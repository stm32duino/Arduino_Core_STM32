# Astyle

[AStyle] is used for coding style checking.

> Artistic Style is a source code indenter, formatter, and beautifier for the C, C++, C++/CLI, Objective‑C, C# and Java programming languages.

GitHub action is used to ensure each PR (Pull Request) and `main` branch of the [STM32 core] follow the code style definition defined. 

Only sources files (`*.h`, `*.hpp`, `*.c`, `*.cpp`) from the following [STM32 core] directory lists are checked:
* `cores/`
* `libraries/`
* `variants/`

## Ignored files
[`.astyleignore`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/CI/astyle/.astyleignore) file contains list of folder to ignore.

## Code style definition

Hereafter the code style definition applied ([`.astylerc`](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/CI/astyle/.astylerc))

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

## Python script

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
                        Astyle installation path
  -r <source root path>, --root <source root path>
                        Source root path to use. Default: <repo path>/Arduino_Core_STM32
```

[AStyle]: http://astyle.sourceforge.net/
[STM32 core]: https://github.com/stm32duino/Arduino_Core_STM32