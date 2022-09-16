#!/usr/bin/env python3

SOURCEFILE_EXTS = (
    ".c",
    ".cpp",
    ".S",
)


def get_default_config():
    return dict(
        sources=set(),
        includedirs=set(),
        extra_libs=set(),
        target="",
        objlib=True,
        ldflags="",
        precompiled="false",
        binaries=dict(),
    )


def parse_configfile(file):
    rawcfg = dict()

    for line in open(file):
        line = line.strip()
        if not line:
            continue
        if line.startswith("#"):
            continue

        key, value = line.split("=", 1)
        key = key
        value = value
        rawcfg[key.strip()] = value.strip()

    cfg = dict()
    cfg["objlib"] = False if rawcfg.get("dot_a_linkage") == "true" else True
    cfg["ldflags"] = rawcfg.get("ldflags", "")
    cfg["precompiled"] = rawcfg.get("precompiled", "false")
    return cfg


def get_sources(dir, recursive=False, relative_to=None):
    if relative_to is None:
        relative_to = dir
    if recursive:
        walker = type(dir).rglob
    else:
        walker = type(dir).glob

    return {
        str(file.relative_to(relative_to)).replace("\\", "/")
        for file in walker(dir, "*")
        if file.is_file() and file.suffix in SOURCEFILE_EXTS
    }


def render(dir, template, config):
    with open(dir / "CMakeLists.txt", "w") as outfile:
        outfile.write(template.render(**config))


def get_static_libs(dir):
    result = dict()
    cpu = ""
    fpconf = "-"  # format: f"{fpu}-{float_abi}"; this makes "-" by default
    for file in dir.glob("src/*/lib*.a"):
        if not file.is_file():
            continue
        cpu = file.parent.name
        result.setdefault(cpu + fpconf, list()).append(file.relative_to(dir))
    for file in dir.glob("src/*/*/lib*.a"):
        if not file.is_file():
            continue
        fpconf = file.parent.name
        cpu = file.parent.parent.name
        result.setdefault(cpu + fpconf, list()).append(file.relative_to(dir))
    return result


def config_for_bareflat(dir, force_recurse=False):
    # no library.properties
    config = get_default_config()

    config["target"] = dir.name
    config["sources"].update(get_sources(dir, recursive=force_recurse))
    config["includedirs"].add(dir.relative_to(dir))

    utils = dir / "utility"
    if utils.exists() and utils.is_dir():
        config["sources"].update(
            get_sources(utils, relative_to=dir, recursive=force_recurse)
        )
        config["includedirs"].add(utils.relative_to(dir))

    return config


def config_for_modern(dir):
    # library.properties present, src/ present
    config = get_default_config()
    config.update(parse_configfile(dir / "library.properties"))

    config["target"] = dir.name
    config["sources"].update(get_sources(dir / "src", recursive=True, relative_to=dir))
    config["includedirs"].add((dir / "src").relative_to(dir))
    config["binaries"].update(get_static_libs(dir))

    return config


def autoconfig(libdir):
    conf_file = libdir / "library.properties"
    srcdir = libdir / "src"
    if (
        conf_file.exists()
        and conf_file.is_file()
        and srcdir.exists()
        and srcdir.is_dir()
    ):
        return config_for_modern(libdir)
    else:
        return config_for_bareflat(libdir)
