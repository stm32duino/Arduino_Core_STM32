#!/usr/bin/env python3

import pathlib
import argparse

from jinja2 import Environment, FileSystemLoader


class Configuration(dict) :

    def __str__(self) :
        if len(self) :
            return super().__str__()
        else :
            return ""

    def __getitem__(self, key) :
        return self.setdefault(key, Configuration())

    def copy(self) :
        # Wrap dict's implementation (returning a dict)
        # Because copying a Configuration should return a Configuration
        return __class__(super().copy())

    def __getattr__(self, attr) :
        return self.__getitem__(attr)
    def __setattr__(self, attr, val) :
        return self.__setitem__(item, attr)

    def set_default_entries(self, mothercfg) :
        for k,v in mothercfg.items() :
            if isinstance(v, dict) :
                self[k].set_default_entries(v)
            else :
                self.setdefault(k, v)

    def evaluate_entries(self, wrt=None) :
        if wrt is None :
            wrt = self

        for k in tuple(self.keys()) :
            if isinstance(self[k], str) :
                try :
                    newv = self[k].format(**wrt)
                except KeyError :
                    raise
                    newv = ""

                self[k] = newv
            else :
                self[k].evaluate_entries(wrt)


def get_fpconf(config) :
    fpu = (config.build.get("fpu") or "-mfpu=").rsplit("=", 1)[1]
    abi = (config.build.get("float-abi") or "-mfloat-abi=").rsplit("=", 1)[1]
    return f"{fpu}-{abi}"

def boardstxt_filter(key) :
    # Remove menu entry labels
    # In our data model, they conflict with the actual configuration they are associated to
    # i.e. Nucleo_144.menu.pnum.NUCLEO_F207ZG would be both a string ("Nucleo F207ZG")
    # and a dict (.build.variant_h=..., .upload.maximum_size=...)


    if key[0] == "menu" :
        # menu.xserial=U(S)ART support
        return True
    if len(key) == 4 and key[1] == "menu":
        # Nucleo_144.menu.pnum.NUCLEO_F207ZG=Nucleo F207ZG
        # Midatronics.menu.upload_method.MassStorage=Mass Storage
        return True

    # Remove upload_method also, that's out of our scope and requires more logic
    if len(key) >= 3 and key[2] == "upload_method" :
        return True

    return False

def platformtxt_filter(key) :
    # reject everything but build.**
    # and also build.info (that's specific to the build system, we'll hard-code it)
    # we don't need anything else from platform.txt
    # +additional stuff might confuse later parts of the script
    # e.g.:

    # compiler.warning_flags=-w
    # compiler.warning_flags.none=-w
    # compiler.warning_flags.default=
    # compiler.warning_flags.more=-Wall
    # compiler.warning_flags.all=-Wall -Wextra

    if key[0] == "build" and key[1] != "info" :
        return False
    return True

def parse_file(infile, reject=None) :
    if reject is None :
        reject = lambda x:False

    config = Configuration()

    for line in open(infile):
        line = line.strip()
        if not line or line.startswith("#") :
            continue
        key, value = line.split("=", 1)
        key = key.strip()
        value = value.strip()

        key = key.split(".")
        ptr = config
        for sub in key[:-1] :
            ptr = ptr[sub]

        if reject(key) :
            ptr.setdefault(key[-1], Configuration())
        else :
            ptr[key[-1]] = value
    return config

def regenerate_template(config, infile, outfile) :
    j2_env = Environment(
        loader=FileSystemLoader(str(infile.parent)), trim_blocks=True, lstrip_blocks=True
    )
    cmake_template = j2_env.get_template(infile.name)

    with open(outfile, "w") as out :
        out.write(cmake_template.render(
            allcfg = config,
        ))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-b", "--boards", type=pathlib.Path, required=True, help="path to boards.txt")
    parser.add_argument("-p", "--platform", type=pathlib.Path, required=True, help="path to platform.txt")
    parser.add_argument("-t", "--template", type=pathlib.Path, required=True, help="path to the jinja template")
    parser.add_argument("-o", "--outfile", type=pathlib.Path, required=True, help="path to the cmake database to generate")

    shargs = parser.parse_args()

    platformtxt_cfg = parse_file(shargs.platform, reject=platformtxt_filter)
    platformtxt_cfg = {"build":platformtxt_cfg["build"]} # whitelist what we need

    boardstxt_cfg = parse_file(shargs.boards, reject=boardstxt_filter)
    del boardstxt_cfg["menu"] # blacklist what we don't need

    # these are optional features to be picked out by the user
    BOARD_FEATURES = [
        "enable_virtio",
        "enable_usb",
        "usb_speed",
        "xSerial",
    ]

    allboards = dict()

    for fam, famcfg in boardstxt_cfg.items() :
        famcfg.set_default_entries(platformtxt_cfg)

        inherit_fam = famcfg.copy()
        # shallow copy; we don't want to impact famcfg so we have to copy before edit/del
        inherit_fam["menu"] = inherit_fam["menu"].copy()
        # del what you iterate over (otherwise you get infinite nesting)
        del inherit_fam["menu"]["pnum"]

        for board, boardcfg in famcfg.menu.pnum.items() :
            boardcfg.set_default_entries(inherit_fam)

            inherit_board = boardcfg.copy()
            del inherit_board["menu"]

            board_feature_names = tuple(boardcfg["menu"].keys())

            for fname in board_feature_names :
                for label, labelcfg in boardcfg["menu"][fname].items() :
                    labelcfg.set_default_entries(inherit_board)
                    labelcfg.evaluate_entries()

            # base config won't manage all the board features, we thus have to mask them out
            for feat in BOARD_FEATURES :
                boardcfg.build[feat] = ""

            boardcfg.evaluate_entries()

            boardcfg["_fpconf"] = get_fpconf(boardcfg)
            allboards[board] = boardcfg

    regenerate_template(allboards, shargs.template, shargs.outfile)
