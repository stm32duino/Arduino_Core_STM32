import argparse
import os
import subprocess
import sys


def run_platformio(example_path, boards):
    return subprocess.call(
        ["platformio", "ci", example_path] + ["--board=" + b for b in boards]
    )


def collect_examples(libs_dir):
    examples = []
    for lib in os.listdir(libs_dir):
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


def main():
    args = parser.parse_args()
    boards = args.board
    if boards is None:
        boards = ["nucleo_f401re"]

    libs_dir = os.path.join(os.environ["GITHUB_WORKSPACE"], "libraries")
    if any(run_platformio(example, boards) for example in collect_examples(libs_dir)):
        sys.exit(1)


if __name__ == "__main__":
    main()
