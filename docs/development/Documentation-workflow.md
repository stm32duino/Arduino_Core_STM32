# Documentation workflow

The STM32 core documentation is maintained in this repository under `docs/`. The pages migrated from the former GitHub wiki are now regular Markdown files; edit those files directly. There is no ongoing wiki synchronization.

## Update documentation

1. Edit the relevant Markdown page under `docs/`, or add a new page there. Keep images and other static assets under `docs/img/` or alongside the page that uses them.
2. Add new pages to the `nav` section in `mkdocs.yml`. The navigation is explicit, so a file that is not listed there will not appear in the sidebar.
3. Use relative links to other Markdown files and verify that image paths resolve from the page containing them.
4. Create a persistent virtual environment under your home directory once, then install or update the documentation dependencies from the core repository:

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

## Pull request checks

The `Documentation build` workflow runs `mkdocs build --strict` on every pull request, including pull requests that do not edit documentation. It also runs on `main` when documentation sources, the MkDocs configuration, its dependencies, or the workflow change.

To make this check a merge requirement, repository maintainers must add the `Documentation build / build` status check to the branch protection rule or ruleset for `main`.

## Publish a release

The documentation publisher uses Mike to keep versioned snapshots on the `gh-pages` branch of `stm32duino/stm32duino.github.io`:

- Documentation changes merged to `main` publish the development version at `/dev/`. The first publish sets `dev` as the site default; later development publishes leave the existing default unchanged.
- Pushing an exact semantic-version tag such as `3.0.0` publishes that release at `/3.0.0/`.
- When the pushed tag is the highest semantic-version tag in the core repository, the workflow also moves the `latest` alias and sets it as the site default. Older release tags are published without changing `latest`.

Use the normal core release process to create and push the release tag. The documentation workflow runs from that tag automatically; no manual Mike command is needed. GitHub release tags must use the exact `MAJOR.MINOR.PATCH` form for this workflow.

## One-time publishing setup

Before the first deployment, maintainers must:

1. Install the publishing GitHub App on `stm32duino/stm32duino.github.io` and grant it `Contents: write` access to that repository. The app does not need to be installed on the core repository.
2. Add the app ID as the `DOCS_PUBLISH_APP_ID` Actions secret and its private key as `DOCS_PUBLISH_APP_PRIVATE_KEY` in `stm32duino/Arduino_Core_STM32`.
3. After the first successful publish creates `gh-pages`, configure GitHub Pages in `stm32duino/stm32duino.github.io` to publish from that branch's root. The existing content on `main` does not need to be copied.

The workflow creates a short-lived, repository-scoped token at publish time. Do not store a personal access token in the repository secrets.
