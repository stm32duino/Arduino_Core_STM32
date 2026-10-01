import re
import subprocess
from pathlib import Path


RELEASE_TAG_PATTERN = re.compile(r"^\d+\.\d+\.\d+$")
DOCS_PATTERN = re.compile(r"^# Docs: (mcu|url|notes|release)=(.*)$")
PART_PATTERN = re.compile(
    r"MP1\d\d[A-F]|WBA\d\d[A-Z][0-9A-Z]|WLE\d[A-Z][0-9A-Z]|W[BL][0-9A-Z]{2}[A-Z][0-9A-Z]"
    r"|[CFGHLU]\d[0-9A-Z]{2}[A-Z][0-9A-Z]"
)
ST_MCU_URL = "https://www.st.com/en/microcontrollers-microprocessors/"

ST_GROUP_LINKS = {
    "Disco": "https://www.st.com/en/evaluation-tools/stm32-discovery-kits.html",
    "Eval": "https://www.st.com/en/evaluation-tools.html",
    "Nucleo_32": "https://www.st.com/en/evaluation-tools/stm32-nucleo-boards.html",
    "Nucleo_64": "https://www.st.com/en/evaluation-tools/stm32-nucleo-boards.html",
    "Nucleo_144": "https://www.st.com/en/evaluation-tools/stm32-nucleo-boards.html",
    "STM32MP1": "https://www.st.com/en/microcontrollers-microprocessors/stm32mp1-series.html",
}


def get_properties(text):
    properties = {}
    for line in text.splitlines():
        if line and not line.startswith("#") and "=" in line:
            key, value = line.split("=", 1)
            properties[key] = value
    return properties


def get_board_definitions(text):
    properties = get_properties(text)
    definitions = []
    for key, label in properties.items():
        parts = key.split(".")
        if len(parts) != 4 or parts[1:3] != ["menu", "pnum"]:
            continue
        group, _, _, option = parts
        prefix = f"{group}.menu.pnum.{option}"
        definitions.append(
            {
                "key": prefix,
                "label": label,
                "board_id": properties.get(f"{prefix}.build.board", option),
                "group": group,
                "group_name": properties.get(f"{group}.name", group),
                "product_line": properties.get(f"{prefix}.build.product_line", ""),
                "series": properties.get(f"{prefix}.build.series", ""),
            }
        )
    return definitions


def get_first_release_versions(repository_root, board_keys):
    if not board_keys:
        return {}
    tags = subprocess.run(
        ["git", "tag", "--list"],
        cwd=repository_root,
        check=True,
        capture_output=True,
        text=True,
    ).stdout.splitlines()
    release_tags = sorted(
        (tag for tag in tags if RELEASE_TAG_PATTERN.fullmatch(tag)),
        key=lambda tag: tuple(int(part) for part in tag.split(".")),
    )

    first_releases = {}
    for tag in release_tags:
        result = subprocess.run(
            ["git", "show", f"{tag}:boards.txt"],
            cwd=repository_root,
            capture_output=True,
            text=True,
        )
        if result.returncode != 0:
            continue
        tagged_keys = {
            definition["key"] for definition in get_board_definitions(result.stdout)
        }
        for board_key in board_keys - first_releases.keys():
            if board_key in tagged_keys:
                first_releases[board_key] = tag
    return first_releases


def get_docs_metadata(boards_text):
    # "# Docs:" comments apply to the next property: a menu.pnum option or a group .name.
    board_metadata = {}
    group_urls = {}
    pending = {}
    for number, line in enumerate(boards_text.splitlines(), 1):
        docs_match = DOCS_PATTERN.match(line)
        if docs_match:
            pending[docs_match.group(1)] = docs_match.group(2)
            continue
        if not pending or line.startswith("#") or "=" not in line:
            continue
        key = line.split("=", 1)[0]
        parts = key.split(".")
        if len(parts) == 4 and parts[1:3] == ["menu", "pnum"]:
            board_metadata[key] = pending
        elif len(parts) == 2 and parts[1] == "name" and pending.keys() == {"url"}:
            group_urls[parts[0]] = pending["url"]
        else:
            raise ValueError(f"boards.txt:{number}: '# Docs:' comment before {key}")
        pending = {}
    return board_metadata, group_urls


def get_mcu_parts(definition, metadata):
    if "mcu" in metadata:
        return [part.strip() for part in metadata["mcu"].split(",") if part.strip()]
    # Product line prefix (e.g. F103 from STM32F103xB) guards against false matches.
    prefix = re.split(r"[xX]", definition["product_line"].removeprefix("STM32"))[0]
    for text in (definition["board_id"], definition["label"]):
        for match in PART_PATTERN.finditer(text.upper()):
            if prefix and match.group().startswith(prefix):
                return [f"STM32{match.group()}"]
    return []


def render_mcu(parts):
    return ", ".join(f"[{part}]({ST_MCU_URL}{part.lower()}.html)" for part in parts)


def render_board_list(repository_root):
    boards_text = (repository_root / "boards.txt").read_text(encoding="utf-8")
    definitions = get_board_definitions(boards_text)
    if not definitions:
        raise ValueError("No board options found in boards.txt")

    board_metadata, group_urls = get_docs_metadata(boards_text)
    first_releases = {
        key: metadata["release"]
        for key, metadata in board_metadata.items()
        if "release" in metadata
    }
    unreleased = {d["key"] for d in definitions} - first_releases.keys()
    first_releases.update(get_first_release_versions(repository_root, unreleased))
    groups = {}
    for definition in definitions:
        groups.setdefault(definition["group"], []).append(definition)

    output = []
    for group, boards in groups.items():
        group_name = boards[0]["group_name"]
        group_url = ST_GROUP_LINKS.get(group) or group_urls.get(group)
        heading_name = (
            group_name
            if group_name.casefold().endswith(" boards")
            else f"{group_name} boards"
        )
        heading = f"[{heading_name}]({group_url})" if group_url else heading_name
        output.extend(
            [
                f"### {heading}",
                "",
                "| Board | STM32 MCU | `build.board` | First release | Notes |",
                "| --- | --- | --- | --- | --- |",
            ]
        )
        for definition in boards:
            metadata = board_metadata.get(definition["key"], {})
            board_url = metadata.get("url") or group_url
            label = definition["label"].replace("|", "\\|")
            if board_url:
                label = f"[{label}]({board_url})"
            mcu = render_mcu(get_mcu_parts(definition, metadata))
            release = first_releases.get(definition["key"], "Next release")
            notes = metadata.get("notes", "").replace("|", "\\|")
            output.append(
                f"| {label} | {mcu} | `{definition['board_id']}` | {release} | {notes} |"
            )
        output.append("")
    return "\n".join(output).strip()


PAGE_HEADER = """# Supported boards

<!-- Generated from boards.txt by docs/hooks/supported_boards.py: do not edit. -->

**Next release** means the board is present in the current core but not in an official release yet. MCU references link to ST's product pages.

<label class="supported-boards-search-label" for="supported-boards-search">Search supported boards</label>
<input id="supported-boards-search" class="supported-boards-search" type="search" placeholder="Board, MCU, build.board, release, or notes" autocomplete="off">
<output id="supported-boards-count" class="supported-boards-count" aria-live="polite"></output>

"""


def generate_page(repository_root):
    page = repository_root / "docs" / "supported-boards" / "index.md"
    content = PAGE_HEADER + render_board_list(repository_root) + "\n"
    # Rewriting an unchanged file would retrigger `mkdocs serve` endlessly.
    if not page.exists() or page.read_text(encoding="utf-8") != content:
        page.write_text(content, encoding="utf-8")


def on_pre_build(config):
    generate_page(Path(config.config_file_path).parent)


if __name__ == "__main__":
    generate_page(Path(__file__).resolve().parents[2])
