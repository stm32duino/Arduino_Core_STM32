# Documentation workflow

The STM32 core documentation is maintained in the `docs/` directory of the `stm32duino/Arduino_Core_STM32` repository. The pages migrated from the former GitHub wiki are now regular Markdown files; edit those files directly. There is no ongoing wiki synchronization.

## Update documentation

1. Edit the relevant Markdown page under `docs/`, or add a new page there. Keep images and other static assets under `docs/img/` or alongside the page that uses them.
2. Add new pages to the `nav` section in `mkdocs.yml`. The navigation is explicit, so a file that is not listed there will not appear in the sidebar.
3. Use relative links to other Markdown files and verify that image paths resolve from the page containing them.
4. The [Supported boards](../supported-boards/index.md) page is generated from `boards.txt`: do not edit it. After changing `boards.txt`, run `python docs/hooks/supported_boards.py` (or any MkDocs build) and commit the updated `docs/supported-boards/index.md`; the documentation check fails if it is out of date. Optional `# Docs: field=value` comments placed directly above a board option (`<group>.menu.pnum.<option>=...`) add metadata: `release`, `mcu`, `url` and `notes`; above a `<group>.name=` line, `url` links the category. Options without `release` get their first release from Git tags, so keep full Git history and tags available when building the documentation.
5. The [Doxygen API reference](#doxygen-api-reference) is generated from the comments in the source code: to change it, edit the comments in the sources, not the documentation pages. Documentation-only builds work without Doxygen installed.
6. Create a persistent virtual environment under your home directory once, then install or update the documentation dependencies from the core repository:

```bash
python3 -m venv "$HOME/.venvs/stm32duino-docs"
"$HOME/.venvs/stm32duino-docs/bin/python" -m pip install -r requirements-docs.txt
"$HOME/.venvs/stm32duino-docs/bin/mkdocs" build --strict
```

   Reuse this environment in later sessions; it lives outside the repository and is not removed by cleaning or switching branches. Rerun the `pip install` command whenever `requirements-docs.txt` changes. Invoke MkDocs from this environment so it uses the installed Material theme instead of a system MkDocs installation. The generated site is written to `site/`, which is ignored by Git. Review informational link diagnostics as well as build failures.

### Preview locally

For normal editing, run the live-reloading MkDocs server from the core repository:

```bash
"$HOME/.venvs/stm32duino-docs/bin/mkdocs" serve
```

Open `http://127.0.0.1:8000/`. This is the fastest way to review content and navigation, but it serves the site at `/` rather than under a version prefix.

To check the URL structure used by GitHub Pages, build into a directory named for a version and serve its parent directory:

```bash
"$HOME/.venvs/stm32duino-docs/bin/mkdocs" build --strict --site-dir /tmp/stm32duino-docs-preview/dev
python -m http.server 8000 --directory /tmp/stm32duino-docs-preview
```

Open `http://127.0.0.1:8000/dev/`. This exercises links under the `/dev/` prefix. Substitute a release such as `3.0.0` or `latest` for `dev` to check those path prefixes. Stop the server with `Ctrl+C`.

The static preview tests the selected version's files and paths, not Mike's deployed version list or redirects. To inspect the actual locally deployed versions and default redirect, use `mike serve` from a checkout whose configured `gh-pages` branch already contains those deployments.

## Doxygen API reference

The source-level API reference (classes, structures, functions and their parameters of the core, its libraries, the STM32 system files and the variants) is generated with [Doxygen](https://www.doxygen.nl/) from the comments in the source code. It is not written by hand: improve it by editing the Doxygen comments in the sources, not the generated pages.

The reference is part of the versioned site and is published at `/<version>/doxygen/`, for example `/dev/doxygen/` or `/latest/doxygen/`. It is linked from the [Arduino API](../API.md) page, from the home page, and from the **Core Reference** section of the navigation.

### Files

| File | Purpose |
| --- | --- |
| `doxygen/Doxyfile` | Doxygen configuration: scope, preprocessor definitions, output location. |
| `doxygen/mainpage.md` | Main page of the reference. |
| `doxygen/html-header.html` | HTML header template: link back to the documentation site and version selector. |
| `doxygen/version-selector.js` | Version selector: lists the versions from the Mike `versions.json` file of the site. |
| `docs/hooks/doxygen.py` | MkDocs hook that adds the generated Doxygen pages to the site under the same version prefix. |

### Comment conventions

- API contracts (`@brief`, `@param`, `@return`, `@note`) are written in the header files. Do not duplicate them in the source file.
- Static and source-only functions are documented directly above their definition in the `.c`/`.cpp` file.
- The ST HAL, LL and CMSIS drivers (`system/Drivers`), the middlewares (`system/Middlewares`) and `cores/arduino/api` (ArduinoCore-API) are excluded from the reference.
- Only documented items are listed (`EXTRACT_ALL = NO`).
- Code under a guard such as `HAL_TIM_MODULE_ENABLED` is only documented if the macro is listed in `PREDEFINED` in `doxygen/Doxyfile`. Add the macro there when a new guard hides documented code.
- Source listings are not generated, to keep every published version small; the reference links to the declarations, and the sources are on GitHub.

### Build locally

Install Doxygen 1.9.8 or later (`sudo apt-get install doxygen` on Debian/Ubuntu), then run, from the repository root:

```bash
STM32_CORE_VERSION=$(sed -n 's/^version=//p' platform.txt) doxygen doxygen/Doxyfile
```

The HTML pages are written to `build/doxygen/`, which is ignored by Git. Open `build/doxygen/index.html` to review them. Doxygen warnings are printed on the standard error: fix those that concern the comments you changed.

To check the reference inside the documentation site, run the Doxygen command above first, then build or serve the site as described in [Update documentation](#update-documentation) and [Preview locally](#preview-locally). When `build/doxygen/` exists, MkDocs adds its pages to the site at `doxygen/`. When it does not, MkDocs adds a placeholder `doxygen/index.html` page, so documentation-only builds, including `mkdocs build --strict`, work without Doxygen installed; the workflows never publish the placeholder because they build the real reference first.

### Version selector

Every Doxygen page shows a **← STM32duino documentation** link, which goes to the home page of the same documentation version, and a **Version** selector. The selector lists the versions published by Mike (`dev`, `latest` and each release) and opens the same page in the selected version. If that page does not exist in the selected version, for example because the version was published before the reference was added or the page was renamed, it opens the Doxygen home page of that version, and then the documentation home page of that version.

The selector reads `versions.json` from the site root, so it only appears on a published site or on a preview that contains it. A preview built with `mkdocs build --site-dir /tmp/stm32duino-docs-preview/dev` has no `versions.json`: the selector is hidden, the link back still works.

### Maintenance

- `doxygen/html-header.html` is based on the default header of Doxygen 1.9.8 (`doxygen -w html header.html footer.html style.css`). When the Doxygen version used by the workflows changes, regenerate the default header, reapply the two additions (the `version-selector.js` script and the `doc-nav` cell with the link and the selector) and check the pages again.
- The Doxygen version is the one installed from the `ubuntu-latest` runner image by the workflows.

## Pull request checks

The `Documentation build` workflow installs Doxygen, builds the API reference, runs `mkdocs build --strict` and fails if the reference is not part of the generated site. It runs on every pull request, including pull requests that do not edit documentation. It also runs on `main` when documentation sources, the Doxygen configuration, the MkDocs configuration, its dependencies, the workflow, or the sources documented by Doxygen (`cores/`, `libraries/`, `variants/`, `system/` except `Drivers/` and `Middlewares/`) change. The `main` branch requires the `Documentation build / build` status check, including for administrators, so a failed or missing result blocks merging.

Doxygen warnings do not fail the check, but they are visible in the log of the `Build Doxygen API reference` step.

If branch protection for `main` is recreated or changed, keep `Documentation build / build` as a required status check.

## Publish a release

The documentation publisher uses Mike to keep versioned snapshots on the `gh-pages` branch of `stm32duino/stm32duino.github.io`. Before running Mike, the workflow installs Doxygen and builds the API reference, so each snapshot contains the Doxygen pages generated from the sources of the commit or tag being published:

- Documentation or documented-source changes merged to `main` publish the development version at `/dev/` (documentation at `/dev/`, API reference at `/dev/doxygen/`). The first publish sets `dev` as the site default; later development publishes leave the existing default unchanged.
- Pushing an exact semantic-version tag such as `3.0.0` publishes that release at `/3.0.0/` (API reference at `/3.0.0/doxygen/`).
- When the pushed tag is the highest semantic-version tag in the core repository, the workflow also moves the `latest` alias and sets it as the site default. Older release tags are published without changing `latest`.

Use the normal core release process to create and push the release tag. The documentation workflow runs from that tag automatically; no manual Mike command is needed. GitHub release tags must use the exact `MAJOR.MINOR.PATCH` form, with a major version below 1000, for this workflow. The legacy date tags such as `2018.1.18` are not release tags: they are ignored when the highest release is computed, so they never prevent `latest` from moving, and a new tag in that form is rejected.

Releases published before the Doxygen reference was added do not contain it; the version selector falls back to the documentation home page of those versions.

### Supported boards after a release

The **First release** column of the [Supported boards](../supported-boards/index.md) page is computed from the Git tags each time the documentation is built. A board that is in `boards.txt` but in no release tag yet shows **Next release**.

- The workflow builds from the release tag, which is fetched with the full history, so the `/<X.Y.Z>/` documentation published for the tag already shows the new release number for the boards it contains. Pages of older versions are not rebuilt and keep their labels.
- The generated `docs/supported-boards/index.md` committed on `main` is not updated by the workflow. Once the tag exists, it differs from a fresh build, so the `Documentation build` check fails on the next pull request until it is regenerated. After pushing a release tag, run `python docs/hooks/supported_boards.py` from a clone that has the tags (`git fetch --tags`) and commit `docs/supported-boards/index.md`.
- The `dev` documentation shows the new release numbers at its next publish.
- To pin a different value for a board, add a `# Docs: release=<version>` comment above its option in `boards.txt`.
