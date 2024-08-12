#!/usr/bin/env python3

import argparse
from pathlib import Path
from jinja2 import Environment, FileSystemLoader
from parse_boards import parse_file


def get_fpconf(config):
    fpu = (config.build.get("fpu") or "-mfpu=").rsplit("=", 1)[1]
    abi = (config.build.get("float-abi") or "-mfloat-abi=").rsplit("=", 1)[1]
    return f"{fpu}-{abi}"


def boardstxt_filter(key):
    # Remove menu entry labels
    # In our data model, they conflict with the actual configuration
    # they are associated to
    # i.e. Nucleo_144.menu.pnum.NUCLEO_F207ZG would be both
    # a string ("Nucleo F207ZG")
    # and a dict (.build.variant_h=..., .upload.maximum_size=...)

    if key[-1] == "svd_file":
        return True

    if key[0] == "menu":
        # menu.xserial=U(S)ART support
        return True
    if len(key) == 4 and key[1] == "menu":
        # Nucleo_144.menu.pnum.NUCLEO_F207ZG=Nucleo F207ZG
        # Midatronics.menu.upload_method.MassStorage=Mass Storage
        return True

    # keep bootloader flags that impact the build
    if len(key) >= 6 and key[1] == "menu" and key[2] == "upload_method":
        if key[3] != "build":
            return False
        return True

    return False


def platformtxt_filter(key):
    # reject everything except build.**, vid.** and pid.**
    # Note that build.info is also rejected
    # (it is specific to the build system, it will be hard-coded)
    # nothing else is needed from platform.txt
    # +additional stuff might confuse later parts of the script
    # e.g.:

    # compiler.warning_flags=-w
    # compiler.warning_flags.none=-w
    # compiler.warning_flags.default=
    # compiler.warning_flags.more=-Wall
    # compiler.warning_flags.all=-Wall -Wextra

    if key[0] == "build" and key[1] != "info":
        return False
    if key[0] == "vid" or key[0] == "pid":
        return False
    return True


def regenerate_template(config, infile, outfile):
    j2_env = Environment(
        loader=FileSystemLoader(str(infile.parent)),
        trim_blocks=True,
        lstrip_blocks=True,
    )
    cmake_template = j2_env.get_template(infile.name)

    with open(outfile, "w") as out:
        out.write(
            cmake_template.render(
                allcfg=config,
            )
        )


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-b", "--boards", type=Path, required=True, help="path to boards.txt"
    )
    parser.add_argument(
        "-p",
        "--platform",
        type=Path,
        required=True,
        help="path to platform.txt",
    )
    parser.add_argument(
        "-t",
        "--template",
        type=Path,
        required=True,
        help="path to the jinja template",
    )
    parser.add_argument(
        "-o",
        "--outfile",
        type=Path,
        required=True,
        help="path to the cmake database to generate",
    )

    shargs = parser.parse_args()

    platformtxt_cfg = parse_file(shargs.platform, reject=platformtxt_filter)
    # whitelist what we need
    platformtxt_cfg = {
        "build": platformtxt_cfg["build"],
        "vid": platformtxt_cfg["vid"],
        "pid": platformtxt_cfg["pid"],
    }

    boardstxt_cfg = parse_file(shargs.boards, reject=boardstxt_filter)
    del boardstxt_cfg["menu"]  # blacklist what we don't need

    # these are optional features to be picked out by the user
    BOARD_FEATURES = ["enable_virtio", "enable_usb", "usb_speed", "xSerial"]

    allboards = dict()

    for fam, famcfg in boardstxt_cfg.items():
        famcfg.set_default_entries(platformtxt_cfg)

        inherit_fam = famcfg.copy()
        # shallow copy;
        # we don't want to impact famcfg so we have to copy before edit/del
        inherit_fam["menu"] = inherit_fam["menu"].copy()
        # del what you iterate over (otherwise you get infinite nesting)
        del inherit_fam["menu"]["pnum"]
        for u_meth, u_meth_cfg in inherit_fam.menu.upload_method.copy().items():
            if "build" not in u_meth_cfg.keys():
                del inherit_fam.menu.upload_method[u_meth]

        for board, boardcfg in famcfg.menu.pnum.items():
            boardcfg["_fpconf"] = get_fpconf(boardcfg)
            boardcfg.set_default_entries(inherit_fam)

            inherit_board = boardcfg.copy()
            del inherit_board["menu"]

            board_feature_names = tuple(boardcfg["menu"].keys())

            for fname in board_feature_names:
                for label, labelcfg in boardcfg["menu"][fname].items():
                    labelcfg.set_default_entries(inherit_board)
                    labelcfg.evaluate_entries()

            # base config won't manage all the board features,
            # we thus have to mask them out
            for feat in BOARD_FEATURES:
                boardcfg.build[feat] = ""

            boardcfg.evaluate_entries()

            allboards[board] = boardcfg
            for mth, mthcfg in boardcfg.menu.upload_method.items():
                if mth.startswith(("hid", "dfuo", "dfu2")):
                    mth = mth.removesuffix("Method")
                    allboards[f"{board}_{mth}"] = mthcfg

    regenerate_template(allboards, shargs.template, shargs.outfile)
