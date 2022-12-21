#!/usr/bin/env python3

"""
Utility module to parse Arduino config files
such as boards.txt/platform.txt.
"""


class Configuration(dict):
    def __str__(self):
        if len(self):
            return super().__str__()
        else:
            return ""

    def __getitem__(self, key):
        return self.setdefault(key, Configuration())

    def copy(self):
        # Wrap dict's implementation (returning a dict)
        # Because copying a Configuration should return a Configuration
        return __class__(super().copy())

    def __getattr__(self, attr):
        return self.__getitem__(attr)

    def __setattr__(self, attr, val):
        return self.__setitem__(val, attr)

    def set_default_entries(self, mothercfg):
        for k, v in mothercfg.items():
            if isinstance(v, dict):
                self[k].set_default_entries(v)
            else:
                self.setdefault(k, v)

    def evaluate_entries(self, wrt=None):
        if wrt is None:
            wrt = self

        for k in tuple(self.keys()):
            if isinstance(self[k], str):
                try:
                    newv = self[k].format(**wrt)
                except KeyError:
                    raise
                    newv = ""

                self[k] = newv
            else:
                self[k].evaluate_entries(wrt)


def default_reject(x):
    return False


def parse_file(infile, reject=None):
    if reject is None:
        reject = default_reject

    config = Configuration()

    for line in open(infile):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        key, value = line.split("=", 1)
        key = key.strip()
        value = value.strip()

        key = key.split(".")
        ptr = config
        for sub in key[:-1]:
            ptr = ptr[sub]

        if reject(key):
            ptr.setdefault(key[-1], Configuration())
        else:
            ptr[key[-1]] = value
    return config
