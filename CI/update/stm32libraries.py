#!/usr/bin/env python3

import concurrent.futures
import json
import os
import re
import subprocess
import sys
from pathlib import Path
from urllib.error import HTTPError, URLError
from urllib.parse import quote, urlencode
from urllib.request import Request, urlopen


SCRIPT_DIR = Path(__file__).resolve().parent
sys.path.append(str(SCRIPT_DIR.parent))
from utils import defaultConfig


REPOSITORY_ROOT = SCRIPT_DIR.parents[1]
CONFIG_PATH = SCRIPT_DIR / "update_config.json"
INDEX_PATH = REPOSITORY_ROOT / "docs" / "libraries" / "index.md"
BEGIN_MARKER = "<!-- BEGIN GENERATED STM32duino library list -->"
END_MARKER = "<!-- END GENERATED STM32duino library list -->"
ORG_NAME = "stm32duino"
GITHUB_API = "https://api.github.com"
RAW_GITHUB = "https://raw.githubusercontent.com"
PER_PAGE = 100
MAX_WORKERS = 8


def check_config():
    if CONFIG_PATH.is_file():
        try:
            config = json.loads(CONFIG_PATH.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError) as error:
            raise RuntimeError(f"cannot read {CONFIG_PATH}: {error}") from error
        if not isinstance(config, dict):
            raise RuntimeError(f"{CONFIG_PATH} must contain a JSON object")
    else:
        config = {}

    if "REPO_STM32DUINO" not in config:
        config["REPO_STM32DUINO"] = str(REPOSITORY_ROOT.parent)
        defaultConfig(CONFIG_PATH, config)

    configured_path = config["REPO_STM32DUINO"]
    if not isinstance(configured_path, str) or not configured_path:
        raise RuntimeError("REPO_STM32DUINO must be a non-empty path")

    repository_path = Path(configured_path).expanduser()
    if not repository_path.is_absolute():
        repository_path = REPOSITORY_ROOT / repository_path
    return repository_path.resolve()


def request_headers(accept):
    headers = {
        "Accept": accept,
        "User-Agent": "stm32duino-library-list-updater",
    }
    token = os.environ.get("GITHUB_TOKEN")
    if token:
        headers["Authorization"] = f"Bearer {token}"
    return headers


def fetch_json(url):
    request = Request(url, headers=request_headers("application/vnd.github+json"))
    try:
        with urlopen(request, timeout=30) as response:
            return json.loads(response.read().decode("utf-8"))
    except (HTTPError, URLError, TimeoutError, json.JSONDecodeError) as error:
        raise RuntimeError(
            f"failed to fetch GitHub API response from {url}: {error}"
        ) from error


def fetch_organization_repositories():
    repositories = []
    page = 1
    while True:
        query = urlencode(
            {
                "type": "public",
                "per_page": PER_PAGE,
                "page": page,
            }
        )
        page_repositories = fetch_json(f"{GITHUB_API}/orgs/{ORG_NAME}/repos?{query}")
        if not isinstance(page_repositories, list):
            raise RuntimeError(
                "GitHub returned an invalid organization repository list"
            )
        repositories.extend(page_repositories)
        if len(page_repositories) < PER_PAGE:
            return repositories
        page += 1


def fetch_manifest(repository):
    branch = repository.get("default_branch")
    if not branch:
        return None

    full_name = repository.get("full_name")
    if not full_name:
        raise RuntimeError("GitHub returned a repository without a full_name")

    branch_path = quote(branch, safe="/")
    url = f"{RAW_GITHUB}/{full_name}/{branch_path}/library.properties"
    request = Request(url, headers=request_headers("text/plain"))
    try:
        with urlopen(request, timeout=30) as response:
            return response.read().decode("utf-8")
    except HTTPError as error:
        if error.code == 404:
            return None
        raise RuntimeError(f"failed to fetch {url}: {error}") from error
    except (URLError, TimeoutError, UnicodeDecodeError) as error:
        raise RuntimeError(f"failed to fetch {url}: {error}") from error


def parse_manifest(text):
    properties = {}
    for line in text.splitlines():
        line = line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        properties[key.strip()] = value.strip()
    return properties


def normalize_remote(url):
    if url.startswith("git@github.com:"):
        url = "https://github.com/" + url.removeprefix("git@github.com:")
    return url.removesuffix(".git").rstrip("/")


def run_git(repository_path, *arguments):
    result = subprocess.run(
        ["git", "-C", str(repository_path), *arguments],
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode:
        message = result.stderr.strip() or result.stdout.strip()
        raise RuntimeError(
            f"git {' '.join(arguments)} failed in {repository_path}: {message}"
        )
    return result.stdout.strip()


def fetch_repository(repository, destination_root):
    full_name = repository["full_name"]
    name = repository["name"]
    branch = repository["default_branch"]
    clone_url = repository["clone_url"]
    destination = destination_root / name

    if destination.exists():
        if not (destination / ".git").exists():
            raise RuntimeError(
                f"{destination} already exists but is not a Git repository"
            )
        origin = run_git(destination, "remote", "get-url", "origin")
        if normalize_remote(origin) != normalize_remote(clone_url):
            raise RuntimeError(
                f"{destination} has unexpected origin {origin!r}; expected {clone_url!r}"
            )
        run_git(destination, "fetch", "--depth=1", "origin", branch)
        revision = "FETCH_HEAD"
    else:
        destination_root.mkdir(parents=True, exist_ok=True)
        result = subprocess.run(
            [
                "git",
                "clone",
                "--depth=1",
                "--single-branch",
                "--branch",
                branch,
                clone_url,
                str(destination),
            ],
            check=False,
            capture_output=True,
            text=True,
        )
        if result.returncode:
            message = result.stderr.strip() or result.stdout.strip()
            raise RuntimeError(f"failed to clone {full_name}: {message}")
        revision = "HEAD"
    manifest = run_git(destination, "show", f"{revision}:library.properties")
    manifest = run_git(destination, "show", f"{revision}:library.properties")
    return parse_manifest(manifest)


def is_expansion_board(repository, properties):
    names = (properties.get("name", ""), repository["name"])
    return any(name.upper().startswith(("X-NUCLEO-", "I-NUCLEO-")) for name in names)


def library_description(repository, properties):
    description = (
        properties.get("sentence")
        or properties.get("paragraph")
        or repository.get("description")
        or ""
    )
    return " ".join(description.split())


def library_dependencies(properties):
    return [
        dependency.strip()
        for dependency in properties.get("depends", "").split(",")
        if dependency.strip()
    ]


def normalize_dependency_name(name):
    name = re.sub(r"\s*\([^)]*\)\s*$", "", name.strip())
    name = re.split(r"\s*@\s*", name, maxsplit=1)[0].strip()
    return name.casefold()


def dependency_links(libraries):
    candidates = {}
    for library in libraries:
        repository = library["repository"]
        properties = library["properties"]
        repository_url = f"https://github.com/{repository['full_name']}"
        names = {
            properties.get("name", ""),
            repository["name"],
        }
        for name in names:
            normalized = normalize_dependency_name(name)
            if normalized:
                candidates.setdefault(normalized, set()).add(repository_url)

    aliases = {}
    for name, urls in candidates.items():
        if name.startswith("stm32duino "):
            aliases.setdefault(name.removeprefix("stm32duino "), set()).update(urls)
    for name, urls in aliases.items():
        candidates.setdefault(name, set()).update(urls)

    return {
        name: next(iter(urls)) for name, urls in candidates.items() if len(urls) == 1
    }


def render_library_entry(library, links):
    repository = library["repository"]
    properties = library["properties"]
    name = properties.get("name", repository["name"])
    description = library_description(repository, properties)
    entry = f"* [{name}](https://github.com/{repository['full_name']})"
    if description:
        entry += f": {description}"

    dependencies = []
    for dependency in library_dependencies(properties):
        url = links.get(normalize_dependency_name(dependency))
        if url:
            dependencies.append(f"[{dependency}]({url})")
        else:
            dependencies.append(f"`{dependency}`")
    if dependencies:
        entry += "\n    * Depends on: " + ", ".join(dependencies)
    return entry


def render_libraries(libraries):
    categories = {}
    expansion_boards = []
    for library in libraries:
        if is_expansion_board(library["repository"], library["properties"]):
            expansion_boards.append(library)
        else:
            category = library["properties"].get("category", "").strip() or "Other"
            categories.setdefault(category, []).append(library)

    links = dependency_links(libraries)

    lines = [
        BEGIN_MARKER,
        "",
        "This list is generated from public STM32duino repositories that contain "
        "a `library.properties` file.",
        "",
    ]
    for category in sorted(categories, key=str.casefold):
        lines.extend((f"### {category}", ""))
        entries = sorted(
            categories[category],
            key=lambda library: library["properties"]
            .get("name", library["repository"]["name"])
            .casefold(),
        )
        for library in entries:
            lines.append(render_library_entry(library, links))
        lines.append("")
    if expansion_boards:
        lines.extend(("## Expansion boards", ""))
        for library in sorted(
            expansion_boards,
            key=lambda item: item["properties"]
            .get("name", item["repository"]["name"])
            .casefold(),
        ):
            lines.append(render_library_entry(library, links))
        lines.append("")
    lines.append(END_MARKER)
    return "\n".join(lines)


def replace_generated_section(document, generated_section):
    start = document.find(BEGIN_MARKER)
    end = document.find(END_MARKER)
    if start < 0 or end < 0 or end < start:
        raise RuntimeError(
            f"{INDEX_PATH} must contain {BEGIN_MARKER!r} before {END_MARKER!r}"
        )
    end += len(END_MARKER)
    return document[:start] + generated_section + document[end:]


def update_index(libraries):
    if not libraries:
        raise RuntimeError("no STM32duino libraries with library.properties were found")
    original = INDEX_PATH.read_text(encoding="utf-8")
    updated = replace_generated_section(original, render_libraries(libraries))
    INDEX_PATH.write_text(updated, encoding="utf-8")


def main():
    destination_root = check_config()
    repositories = fetch_organization_repositories()
    candidates = []

    with concurrent.futures.ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:
        futures = {
            executor.submit(fetch_manifest, repository): repository
            for repository in repositories
            if repository.get("default_branch") and repository.get("clone_url")
        }
        for future in concurrent.futures.as_completed(futures):
            repository = futures[future]
            if future.result() is not None:
                candidates.append(repository)

    libraries = []
    for repository in sorted(candidates, key=lambda item: item["name"].casefold()):
        print(f"Fetching {repository['full_name']}...")
        properties = fetch_repository(repository, destination_root)
        libraries.append({"repository": repository, "properties": properties})

    update_index(libraries)
    print(f"Updated {INDEX_PATH} with {len(libraries)} libraries.")


if __name__ == "__main__":
    try:
        main()
    except (OSError, RuntimeError) as error:
        print(f"Error: {error}", file=sys.stderr)
        sys.exit(1)
