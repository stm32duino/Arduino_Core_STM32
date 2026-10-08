# Contributing

Thank you for contributing to the STM32 Arduino core. Before opening an issue or pull request, make sure the change is directed to the correct repository and can be reproduced or reviewed by another contributor.

See the repository's [full contributing guide](https://github.com/stm32duino/Arduino_Core_STM32/blob/main/CONTRIBUTING.md) for the project checklist and commit-message conventions.

## Report an issue

Before opening an issue:

- Confirm that you are using a current STM32 core and library version.
- Search existing issues and the [STM32duino community forum](http://stm32duino.com).
- Confirm that the issue belongs to the [Arduino core repository](https://github.com/stm32duino/Arduino_Core_STM32). Other STM32duino projects are listed in the full contributing guide.

Provide the expected behavior, the actual behavior, complete error messages, reproduction steps, and the smallest complete example that demonstrates the problem.

## Open a pull request

A pull request should explain:

- What problem it solves or what behavior it adds
- Why the change is needed
- How it was tested
- Any affected boards, examples, libraries, or documentation

Keep commits focused and update the documentation when the user-visible behavior changes.

## Prepare the change

Use the guide that matches the type of change:

- [Using the Git repository](Using-git-repository.md) explains how to work with a local core checkout.
- [Adding a board variant](Add-a-new-variant/overview.md) covers new generic and dedicated board variants.
- [Code style and AStyle](Astyle.md) explains the required formatting and local validation commands.
- [Documentation workflow](Documentation-workflow.md) explains how to edit, build, preview, and publish documentation.
- [Source locations](Where-are-sources.md) identifies the main core and board-package directories.

## Validate the change

Run the checks relevant to the files you changed. Documentation changes must pass the strict MkDocs build:

```console
set_http_https_proxy && "$HOME/.venvs/stm32duino-docs/bin/mkdocs" build --strict
```

For source changes, run the applicable build, example, or test checks for the affected board families. Run the AStyle check for changes under `cores/`, `libraries/`, or `variants/`.

Include the commands and important results in the pull request description.

## After the pull request is merged

Update related documentation if the merged change affects user-facing behavior, supported boards, examples, build options, or upload and debugging workflows.
