# OpenAMP lib build check docker action

This action test builds for a specified target.

## Inputs

### `target`

**Required** the build target. Default `"linux"`.
The supported taget are:
  linux
  generic arm
  zephyr


## Example usage

uses: ./.github/actions/build_ci
with:
  target: linux