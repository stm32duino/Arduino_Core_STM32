# AStyle

[AStyle] is used to format and check the coding style of the STM32 core.

> Artistic Style is a source code indenter, formatter, and beautifier for the C, C++, C++/CLI, Objective‑C, C# and Java programming languages.

The GitHub Actions workflow checks pull requests and the `main` branch against the style definition in [`.astylerc`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/CI/astyle/.astylerc).

## Installation

AStyle **3.1 is required**. Newer AStyle versions are not compatible with the STM32duino style configuration. Install the 3.1 package for your operating system, or download it from the [AStyle project page][AStyle].

For Debian or Ubuntu, use the command below only when the configured package repository provides AStyle 3.1:

```console
sudo apt install astyle
```

Verify the installation:

```console
astyle --version
```

Confirm that the reported version is exactly `3.1`. A package manager may provide a newer, incompatible version; use a pinned 3.1 package when necessary.

The `astyle.py` script looks for the `astyle` executable in `PATH`. If it is installed in a custom directory, provide that directory with the `-p` option.

## Files checked

The script checks C and C++ source files with these extensions:

- `*.h`
- `*.hpp`
- `*.c`
- `*.cpp`

When run against the repository root, the relevant source directories are:

- `cores/`
- `libraries/`
- `variants/`

Paths listed in [`.astyleignore`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/CI/astyle/.astyleignore) are excluded from formatting.

## Run AStyle

Run these commands from the root of the `Arduino_Core_STM32` repository. The script formats files in place, so review the changes before committing them.

Format all matching files:

```console
python3 CI/astyle/astyle.py -r .
```

Format only files changed relative to the default remote branch (`remotes/origin/main`):

```console
python3 CI/astyle/astyle.py -g
```

Format files changed relative to a specific branch:

```console
python3 CI/astyle/astyle.py -b origin/main
```

The `-g` and `-b` options require the referenced Git branch to be available locally. Fetch the branch first if necessary.

To use an AStyle installation outside `PATH`, provide the directory containing the executable:

```console
python3 CI/astyle/astyle.py -p /path/to/astyle-directory
```

The script writes its formatter output to `astyle.out` in the current directory. This file is temporary and can be removed after reviewing the result.

## Review the result

Use Git to review files changed by the formatter:

```console
git diff -- cores libraries variants
git diff --check
```

If the formatter changed files unexpectedly, check the selected source root and [`.astyleignore`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/CI/astyle/.astyleignore) before committing. Restore unwanted changes with the normal Git workflow for your branch.

## Troubleshooting

- `Astyle binary not found`: install AStyle or provide the directory containing the executable with `-p`.
- `Astyle minimum version required 3.1`: install the compatible AStyle 3.1 package. A newer version is not a valid replacement.
- `No file found to apply Astyle`: check that the source root exists and that the selected branch contains matching C or C++ files.
- Git-diff mode fails: fetch the branch named by `-g` or `-b`, then run the command again.

## Style definition

The following configuration is applied through [`.astylerc`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/CI/astyle/.astylerc):

- K&R brace style with braces added to single-line statements
- Two-space indentation with tabs converted to spaces
- Indented classes, namespaces, switches, cases, and preprocessor blocks
- Padding around operators and control-statement headers
- Pointer and reference operators aligned with the name
- Linux line endings
- No backup files
- Continuation indentation limited to 120 columns

The complete configuration is:

```bash
# STM32duino code style definition file for Astyle

# Don't create backup files, let git handle it
suffix=none

# K&R style
style=kr

# 1 TBS addition to k&r, add braces to one liners
# Use -j as it was changed in astyle from brackets to braces, this way it is compatible with older astyle versions
-j

# 2 spaces, convert tabs to spaces
indent=spaces=2
convert-tabs

# Indent switches and cases
indent-classes
indent-switches
indent-cases
indent-col1-comments

# Remove spaces in and around parentheses
unpad-paren

# Insert a space after if, while, for, and around operators
pad-header
pad-oper

# Pointer/reference operators go next to the name (on the right)
align-pointer=name
align-reference=name

# Attach { for classes and namespaces
attach-namespaces
attach-classes

# Extend longer lines, define maximum 120 value. This results in aligned code,
# otherwise the lines are broken and not consistent
max-continuation-indent=120

# if you like one-liners, keep them
keep-one-line-statements
```

## Continuous integration

The `Check code formatting with astyle` GitHub Actions workflow runs for pull requests and pushes to `main`. It uses the same `.astylerc` and `.astyleignore` files documented above and the AStyle 3.1 package provided by [`stm32duino/actions/astyle-check`](https://github.com/stm32duino/actions/tree/main/astyle-check). If formatting errors are found, the workflow reports the formatter output in the failed job.

## Python script reference

Python script [`astyle.py`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/CI/astyle/astyle.py) is provided to ease use of [AStyle]:

```stdout
usage: astyle.py [-h] [-d <code style definition file>] [-g | -b <branch name>] [-i <ignore file>] [-p <astyle install path>]
                 [-r <source root path>]

Launch astyle on source files.

options:
  -h, --help            show this help message and exit
  -d <code style definition file>, --definition <code style definition file>
                        Code style definition file for Astyle. Default: <repo path>/Arduino_Core_STM32/CI/astyle/.astylerc
  -g, --gitdiff         Use changes files from git default branch. Default: {git_branch}
  -b <branch name>, --branch <branch name>
                        Use changes files from git specified branch.
  -i <ignore file>, --ignore <ignore file>
                        File containing path to ignore. Default: <repo path>/Arduino_Core_STM32/CI/astyle/.astyleignore
  -p <astyle install path>, --path <astyle install path>
                        Directory containing the Astyle installation
  -r <source root path>, --root <source root path>
                        Source root path to use. Default: <repo path>/Arduino_Core_STM32
```

[AStyle]: http://astyle.sourceforge.net/
[STM32 core]: https://github.com/stm32duino/Arduino_Core_STM32
