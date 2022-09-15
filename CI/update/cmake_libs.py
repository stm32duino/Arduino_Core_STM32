
import sys
from pathlib import Path

from jinja2 import Environment, FileSystemLoader

if len(sys.argv) != 2 :
    print("Usage: cmake_libs.py <.../libraries>")
    print("Generates a CMakeLists.txt describing a library")
    print("The resulting object library will be named like the folder.")


SOURCEFILE_EXTS = (".c", ".cpp", ".S", )

rootdir = Path(sys.argv[1]).resolve()
script_path = Path(__file__).parent.resolve()
templates_dir = script_path / "templates"
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("CMakeLists.txt")

if not (rootdir.exists() and rootdir.name == "libraries") :
    print(f"Invalid variant folder : {rootdir}")
    exit()

for lib in rootdir.iterdir() :
    # technically several variants may be gathered in the same folder
    if not lib.is_dir() :
        continue

    sources = [
        file.relative_to(lib)
        for file in (lib / "src").rglob("*")
        if file.is_file() and file.suffix in SOURCEFILE_EXTS
    ]

    with open(lib / "CMakeLists.txt", "w") as outfile :
        outfile.write(cmake_template.render(
            target=lib.name,
            objlib=True,
            sources=sources,
            includedir=(lib / "src").relative_to(lib),
        ))
