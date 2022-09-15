
import sys
from pathlib import Path

from jinja2 import Environment, FileSystemLoader

if len(sys.argv) != 2 :
    print("Usage: cmake_variant.py <.../variants>")
    print("Generates a CMakeLists.txt describing a variant folder")
    print("The resulting static library will be named \"variant\".")


SOURCEFILE_EXTS = (".c", ".cpp", ".S")

rootdir = Path(sys.argv[1]).resolve()
script_path = Path(__file__).parent.resolve()
templates_dir = script_path / "templates"
j2_env = Environment(
    loader=FileSystemLoader(str(templates_dir)), trim_blocks=True, lstrip_blocks=True
)
cmake_template = j2_env.get_template("CMakeLists.txt")

if not (rootdir.exists() and rootdir.name == "variants") :
    print(f"Invalid variant folder : {rootdir}")
    exit()

for family in rootdir.iterdir() :
    if not family.is_dir() :
        continue
    for variant in family.iterdir() :
        # technically several variants may be gathered in the same folder
        if not variant.is_dir() :
            continue

        sources = [
            file.relative_to(variant)
            for file in variant.iterdir()
            if file.is_file() and file.suffix in SOURCEFILE_EXTS
        ]

        with open(variant / "CMakeLists.txt", "w") as outfile :
            # I'd gladly name the target something less generic;
            # if only the variant folder were a valid identifier...
            outfile.write(cmake_template.render(
                target="variant",
                objlib=False,
                sources=sources,
                includedir=None,
            ))
