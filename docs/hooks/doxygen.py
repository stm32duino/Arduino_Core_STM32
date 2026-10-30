import logging
from pathlib import Path

from mkdocs.structure.files import File

log = logging.getLogger("mkdocs.hooks.doxygen")

# Doxygen HTML output, see doxygen/Doxyfile (relative to the repository root).
# Its last component is the folder of the generated site: <site>/<version>/doxygen/
DOXYGEN_OUTPUT = Path("build/doxygen")

PLACEHOLDER = """<!DOCTYPE html>
<html lang="en">
<head><meta charset="utf-8"><title>Doxygen API reference not generated</title></head>
<body>
<h1>Doxygen API reference not generated</h1>
<p>This build does not contain the Doxygen API reference.
Run <code>doxygen doxygen/Doxyfile</code> from the repository root, then build the site again.</p>
</body>
</html>
"""


def on_files(files, config):
    """Add the Doxygen HTML pages to the site, under the same version prefix."""
    output = Path(config.config_file_path).parent / DOXYGEN_OUTPUT
    if not (output / "index.html").is_file():
        # Keep the links to the reference valid in builds made without Doxygen.
        log.info(
            "Doxygen output not found in '%s': adding a placeholder page. "
            "Run 'doxygen doxygen/Doxyfile' before building to include the API reference.",
            DOXYGEN_OUTPUT,
        )
        files.append(File.generated(config, f"{DOXYGEN_OUTPUT.name}/index.html", content=PLACEHOLDER))
        return files

    count = 0
    for path in sorted(output.rglob("*")):
        if path.is_file():
            files.append(
                File(
                    path.relative_to(output.parent).as_posix(),
                    str(output.parent),
                    config.site_dir,
                    config.use_directory_urls,
                )
            )
            count += 1
    log.info("Added %d Doxygen API reference files from '%s'", count, DOXYGEN_OUTPUT)
    return files
