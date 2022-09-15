
import sys
from pathlib import Path

from jinja2 import Environment, FileSystemLoader

if len(sys.argv) != 2 :
    print("Usage: cmake_core.py <.../cores/arduino>")
    print("Generates a CMakeLists.txt describing a core")
    print("The resulting static library will be named \"core\".")


SOURCEFILE_EXTS = (".c", ".cpp", ".S")

rootdir = Path(sys.argv[1]).resolve()
script_path = Path(__file__).parent.resolve()
templates_dir = script_path / "templates"
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("CMakeLists.txt")

sources = [
    file.relative_to(rootdir)
    for file in rootdir.rglob("*")
    if file.is_file() and file.suffix in SOURCEFILE_EXTS
]

with open(rootdir / "CMakeLists.txt", "w") as outfile :
    outfile.write(cmake_template.render(
        target="core",
        objlib=False,
        sources=sources,
        includedir=None,
    ))
