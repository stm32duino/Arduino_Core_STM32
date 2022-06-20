import argparse
import os
import subprocess
import sys

# Libraries that are not meant to be checked in CI by default
DEFAULT_IGNORED_LIBRARIES = (
    "keyboard",
    "mouse"
)


def run_platformio(example_path, boards):
    return subprocess.call(
        ["platformio", "ci", example_path] + ["--board=" + b for b in boards]
    )


def collect_examples(libs_dir, ignored_libraries=None):
    ignored_libraries = ignored_libraries or []
    examples = []
    for lib in os.listdir(libs_dir):
        if lib.lower() in ignored_libraries:
            print(f"Skipping examples from the `{lib}` library...")
            continue
        lib_dir = os.path.join(libs_dir, lib)
        examples_dir = os.path.join(lib_dir, "examples")
        if os.path.isdir(examples_dir):
            examples.extend(
                [os.path.join(examples_dir, ex) for ex in os.listdir(examples_dir)]
            )
    return examples


parser = argparse.ArgumentParser(description="Basic PlatformIO runner")

parser.add_argument(
    "-b", "--board", action="append", help="board ID used for PlatformIO project"
)
parser.add_argument(
    "-i", "--ignore-library", action="append", help="Library name to ignore when collecting project examples"
)


def main():
    args = parser.parse_args()
    boards = args.board
    if boards is None:
        boards = ["nucleo_f401re"]

    ignored_libraries = args.ignore_library
    if ignored_libraries is None:
        ignored_libraries = DEFAULT_IGNORED_LIBRARIES

    libs_dir = os.path.join(os.environ["GITHUB_WORKSPACE"], "libraries")
    if any(run_platformio(example, boards) for example in collect_examples(libs_dir, ignored_libraries)):
        sys.exit(1)


if __name__ == "__main__":
    main()
