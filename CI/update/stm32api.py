import argparse
import shutil
import subprocess
import sys
from pathlib import Path

script_path = Path(__file__).parent.resolve()
sys.path.append(str(script_path.parent))
from utils import execute_cmd

# Core STM32 repo root (Arduino_Core_STM32)
core_path = script_path.parent.parent.resolve()

# ArduinoCore-API submodule path
api_submodule_path = core_path / "cores" / "arduino" / "api"

# Git remotes / branches
arduino_api_remote_name = "arduinocoreapi"
arduino_api_remote_url = "https://github.com/arduino/ArduinoCore-API.git"
arduino_api_default_branch = "master"  # upstream default branch
api_local_branch = "main"  # local branch used in the submodule

# -----------------------------------------------------------------------------
# Helpers
# -----------------------------------------------------------------------------


def getOpenApiPatchesPrNumbers():

    print("== Fetch open PRs targeting 'api-patches' ==")

    label_name = "hardware neutral patches"
    try:
        # gh pr list --base api-patches --state open --json number --jq '.[].number'
        output = subprocess.check_output(
            [
                "gh",
                "pr",
                "list",
                "--repo",
                "stm32duino/ArduinoCore-API",
                "--base",
                "api-patches",
                "--state",
                "open",
                "--label",
                label_name,
                "--json",
                "number",
                "--jq",
                ".[].number",
            ],
            text=True,
        )
    except subprocess.CalledProcessError as e:
        print("ERROR: failed to fetch PR list via gh CLI")
        print(e)
        return []

    pr_numbers = []
    for line in output.splitlines():
        line = line.strip()
        if not line:
            continue
        try:
            pr_numbers.append(int(line))
        except ValueError:
            print(f"WARNING: unexpected PR number value: {line}")
    pr_numbers.sort()
    print(f"  Found open PRs on 'api-patches': {pr_numbers}")
    return pr_numbers


def run_api(cmd, capture_output=True):

    if capture_output:
        return subprocess.check_output(
            cmd, cwd=str(api_submodule_path), text=True
        ).strip()
    else:
        subprocess.check_call(cmd, cwd=str(api_submodule_path))


def checkApiSubmodule():

    if not api_submodule_path.exists():
        print(f"Could not find ArduinoCore-API submodule: {api_submodule_path}!")
        print("Please run: git submodule update --init")
        sys.exit(1)


def ensureArduinoRemote():

    remotes = run_api(["git", "remote"]).splitlines()
    if arduino_api_remote_name not in remotes:
        print(f"Add remote {arduino_api_remote_name} -> {arduino_api_remote_url}")
        run_api(
            ["git", "remote", "add", arduino_api_remote_name, arduino_api_remote_url],
            capture_output=False,
        )
    else:
        url = run_api(["git", "remote", "get-url", arduino_api_remote_name])
        if url != arduino_api_remote_url:
            print(
                f"Update URL of {arduino_api_remote_name}: {url} -> {arduino_api_remote_url}"
            )
            run_api(
                [
                    "git",
                    "remote",
                    "set-url",
                    arduino_api_remote_name,
                    arduino_api_remote_url,
                ],
                capture_output=False,
            )


def ensureApiClean():
    status = run_api(["git", "status", "--porcelain"])
    if status:
        print("Working tree NOT clean in submodule cores/arduino/api, abort.")
        print(status)
        sys.exit(1)


def abortAnyAm():

    try:
        run_api(["git", "am", "--abort"], capture_output=False)
        print("  (git am --abort executed to clear previous state)")
    except subprocess.CalledProcessError:
        # No rebase-apply directory, nothing to abort
        pass


def getLatestArduinoTag():

    # Ensure we have up-to-date tags
    run_api(["git", "fetch", arduino_api_remote_name, "--tags"], capture_output=False)

    # List tags sorted by creation date (newest first) and pick the first one
    tags = run_api(["git", "tag", "--sort=-creatordate"]).splitlines()
    if not tags:
        print("WARNING: no tags found on arduinocoreapi, falling back to master")
        return None

    latest_tag = tags[0].strip()
    print(f"Latest ArduinoCore-API tag: {latest_tag}")
    return latest_tag


def resyncApiToArduinoLatestTag():

    print("== Fetch arduinocoreapi (including tags) in cores/arduino/api ==")
    run_api(["git", "fetch", arduino_api_remote_name, "--tags"], capture_output=False)

    print(f"== Checkout {api_local_branch} ==")
    run_api(["git", "checkout", api_local_branch], capture_output=False)

    latest_tag = getLatestArduinoTag()
    if latest_tag is None:
        # fallback: use master HEAD if no tag exists
        target = f"{arduino_api_remote_name}/{arduino_api_default_branch}"
    else:
        # Reset directly to that tag (not to a describe string)
        target = latest_tag

    print(f"== Reset {api_local_branch} to {target} (local only) ==")
    run_api(["git", "reset", "--hard", target], capture_output=False)

    head = run_api(["git", "rev-parse", "HEAD"])
    log = run_api(["git", "log", "-1", "--oneline"])
    print(f"  HEAD after reset : {head}")
    print(f"  Last commit      : {log}")


def applyArduinoApiPr(pr_number):

    print(f"== Download and apply stm32duino PR #{pr_number} using gh CLI == ")

    # gh pr diff --repo stm32duino/ArduinoCore-API <PR> --patch
    try:
        patch_content = subprocess.check_output(
            [
                "gh",
                "pr",
                "diff",
                "--repo",
                "stm32duino/ArduinoCore-API",
                str(pr_number),
                "--patch",
            ],
            text=True,
        )
    except subprocess.CalledProcessError as e:
        print(f"ERROR: failed to fetch PR #{pr_number} patch via gh CLI")
        print(e)
        sys.exit(1)

    # Check that the patch applies cleanly using stdin
    print("  Check patch with git apply --check ...")
    check = subprocess.Popen(
        ["git", "apply", "--check", "-"],
        cwd=str(api_submodule_path),
        stdin=subprocess.PIPE,
        text=True,
    )
    check.communicate(input=patch_content)
    if check.returncode != 0:
        print(f"ERROR: patch for PR #{pr_number} does not apply cleanly.")
        sys.exit(1)

    # Ensure no previous git am is in progress
    abortAnyAm()

    print("  Apply patch with git am ...")
    am = subprocess.Popen(
        ["git", "am", "--keep-non-patch", "--signoff"],
        cwd=str(api_submodule_path),
        stdin=subprocess.PIPE,
        text=True,
    )
    am.communicate(input=patch_content)
    if am.returncode != 0:
        print(f"ERROR: git am failed for PR #{pr_number}.")
        sys.exit(1)


def applyPatch(repo_path):

    # First check if some patch need to be applied
    api_patch_path = script_path / "patch" / "api"
    patch_list = []
    for file in sorted(api_patch_path.iterdir()):
        if file.name.endswith(".patch"):
            patch_list.append(api_patch_path / file)

    if len(patch_list):
        patch_failed = []
        print(f"Apply {len(patch_list)} patch{'' if len(patch_list) == 1 else 'es'}")
        for patch in patch_list:
            try:
                # Test the patch before apply it
                status = execute_cmd(
                    ["git", "-C", repo_path, "apply", "--check", str(patch)],
                    subprocess.STDOUT,
                )
                if status:
                    # patch can't be applied cleanly
                    patch_failed.append([patch, status])
                    continue
                # Apply the patch
                status = execute_cmd(
                    [
                        "git",
                        "-C",
                        repo_path,
                        "am",
                        "--keep-non-patch",
                        "--quiet",
                        "--signoff",
                        str(patch),
                    ],
                    None,
                )
            except subprocess.CalledProcessError as e:
                patch_failed.append([patch, e.cmd, e.output.decode("utf-8")])

        if len(patch_failed):
            for fp in patch_failed:
                e_out = "" if len(fp) == 2 else f"\n--> {fp[2]}"
                print(f"Failed to apply {fp[0]}:\n{fp[1]}{e_out}")


def reworkTree():

    print("== Rework ArduinoCore-API tree for STM32 ==")

    keep_files_exact = {"LICENSE"}

    for entry in api_submodule_path.iterdir():
        name = entry.name

        # Never touch .git
        if name == ".git":
            continue

        # Keep .github directory
        if name == ".github" and entry.is_dir():
            continue

        # Keep api directory (we transform inside it)
        if name == "api" and entry.is_dir():
            continue

        # Keep LICENSE
        if name in keep_files_exact and entry.is_file():
            continue

        # Keep README* files
        if entry.is_file() and name.startswith("README"):
            continue

        # Everything else is removed
        if entry.is_dir():
            print(f"  Remove directory: {entry}")
            shutil.rmtree(entry)
        else:
            print(f"  Remove file     : {entry}")
            entry.unlink()

    # Flatten api/* into root (cores/arduino/api/)
    api_dir = api_submodule_path / "api"

    if not api_dir.exists():
        print("  No 'api' directory found to flatten, nothing to do.")
        return

    print(f"  Flattening {api_dir} into {api_submodule_path}")

    for entry in api_dir.iterdir():
        dest = api_submodule_path / entry.name
        if dest.exists():
            print(f"  WARNING: destination already exists, skipping: {dest}")
            continue
        print(f"    Move {entry} -> {dest}")
        entry.rename(dest)

    # Remove now-empty api/ directory
    try:
        api_dir.rmdir()
        print(f"  Removed empty directory: {api_dir}")
    except OSError:
        print(f"  WARNING: {api_dir} not empty, please check manually.")


def commitReworkedTree():

    print("== Commit reworked ArduinoCore-API tree ==")

    status = run_api(["git", "status", "--porcelain"])
    if not status:
        print("  No changes to commit.")
        return

    run_api(["git", "add", "--all"], capture_output=False)

    commit_msg = "refactor: keep only api/ folder for STM32duino usage"
    run_api(
        ["git", "commit", "--all", "--signoff", f"--message={commit_msg}"],
        capture_output=False,
    )

    print("  Commit created:")
    log = run_api(["git", "log", "-1", "--oneline"])
    print(f"  {log}")


# -----------------------------------------------------------------------------
# main
# -----------------------------------------------------------------------------


def main():
    parser = argparse.ArgumentParser(
        description="Sync and patch ArduinoCore-API submodule for STM32 core"
    )
    _ = parser.parse_args()

    print(f"Core repo path : {core_path}")
    print(f"API submodule  : {api_submodule_path}")

    checkApiSubmodule()
    ensureArduinoRemote()
    ensureApiClean()
    resyncApiToArduinoLatestTag()

    pr_numbers = getOpenApiPatchesPrNumbers()

    # Apply stm32duino API-upstream PRs via GH CLI
    for pr in pr_numbers:
        applyArduinoApiPr(pr)

    applyPatch(api_submodule_path)

    # Rework the tree layout for STM32 usage
    reworkTree()

    # Commit the reworked tree
    commitReworkedTree()

    print("== Log after applying PRs and reworking tree == ")
    log = run_api(["git", "log", "-5", "--oneline"])
    print(log)


if __name__ == "__main__":
    main()
