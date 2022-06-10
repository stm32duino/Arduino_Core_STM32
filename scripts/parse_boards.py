#!/usr/bin/env python3

import sys
import pathlib
from jinja2 import Environment, FileSystemLoader


class Configuration(dict) :

    def __str__(self) :
        if len(self) :
            return super().__str__()
        else :
            return ""

    def __getitem__(self, key) :
        return self.setdefault(key, Configuration())

    def __setitem__(self, key, val) :
        if key in self.keys() and val != self[key] :
            raise KeyError("Key exists " + key)
        else :
            super().__setitem__(key, val)
            # self.children[key] = val


    def __getattr__(self, attr) :
        return self.__getitem__(attr)
    def __setattr__(self, attr, val) :
        return self.__setitem__(item, attr)

    def set_default_entries(self, mothercfg) :
        for k,v in mothercfg.items() :
            if k in self and isinstance(v, dict) :
                self[k].set_default_entries(v)
            else :
                self.setdefault(k, v)

    def evaluate_entries(self, wrt=None) :
        if wrt is None :
            wrt = self

        result = Configuration()

        for k in tuple(self.keys()) :
            if isinstance(self[k], str) :
                try :
                    newv = self[k].format(**wrt)
                except KeyError :
                    newv = ""

                result[k] = newv
            else :
                result[k] = self[k].evaluate_entries(wrt)

        return result




def is_menulabel(key) :
    if key[0] == "menu" :
        # menu.xserial=U(S)ART support
        return True
    if len(key) == 4 and key[1] == "menu":
        # Nucleo_144.menu.pnum.NUCLEO_F207ZG=Nucleo F207ZG
        # Midatronics.menu.upload_method.MassStorage=Mass Storage
        return True

    return False

def parse_file(infile) :
    config = Configuration()

    for line in open(infile):
        line = line.strip()
        if not line or line.startswith("#") :
            continue
        key, value = line.split("=", 1)
        key = key.strip()
        value = value.strip()

        key = key.split(".")
        if not is_menulabel(key) :
            ptr = config
            for sub in key[:-1] :
                ptr = ptr[sub]
            ptr[key[-1]] = value
    return config

def flatten_family(famconfig) :
    boards = famconfig.menu.pop("pnum")
    for board in boards.values() :
        board.set_default_entries(famconfig)

    return boards

def flatten_config(config) :
    flat = dict()
    for fam in config.values() :
        flat.update(flatten_family(fam))
    return flat

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
    if len(sys.argv) != 4 :
        print("Usage: ./parse_boards.py <boardsfile> <template> <outfile>")
        exit(1)

    boardsfile = pathlib.Path(sys.argv[1])
    templatefile = pathlib.Path(sys.argv[2])
    outfile = pathlib.Path(sys.argv[3])

    if not boardsfile.exists() and boardsfile.is_file() :
        print(f"Can't find file {boardsfile}")
        exit(1)
    if not templatefile.exists() and templatefile.is_file() :
        print(f"Can't find file {templatefile}")
        exit(1)

    rawcfg = flatten_config(parse_file(boardsfile))
    finalcfg = {board: cfg.evaluate_entries() for board, cfg in rawcfg.items()}
    regenerate_template(finalcfg, templatefile, outfile)
