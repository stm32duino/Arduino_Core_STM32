#!/usr/bin/env python3

import pathlib
import argparse

import graphviz

parser = argparse.ArgumentParser()
parser.add_argument(
    "-m", "--mapfile", type=pathlib.Path, required=True, help="path to ld's map file"
)
parser.add_argument(
    "-f", "--fullgv", type=pathlib.Path, help="file to write the full graph to"
)
parser.add_argument(
    "-s", "--summarygv", type=pathlib.Path, help="file to write the summarized graph to"
)

shargs = parser.parse_args()


def parse_file(mapf):
    fullgraph = graphviz.Digraph(graph_attr=dict(overlap="False"))
    summary = graphviz.Digraph(strict=True, graph_attr=dict(overlap="False"))

    start = "Archive member included to satisfy reference by file (symbol)"
    stop = "Discarded input sections"
    for line in mapf:
        if line.startswith(start):
            break

    provider = None
    demander = None
    sym = None
    for line in mapf:
        if line.isspace():
            continue
        if line.startswith(stop):
            break

        if line.startswith((" ", "\t")):
            try:
                demander, sym = line.strip().rsplit(") (", 1)
                demander = demander + ")"
                sym = "(" + sym
            except Exception:
                continue
        else:
            provider = line.strip()

        if provider and demander and sym:
            # .split("(")[0] gets the lib ; without this you get the obj
            objdemander = demander.rsplit("/", 1)[1]
            objprovider = provider.rsplit("/", 1)[1]
            libdemander = objdemander.split("(")[0]
            libprovider = objprovider.split("(")[0]

            fullgraph.edge(objdemander, objprovider, tooltip=sym)
            summary.edge(libdemander, libprovider)

            provider = None
            demander = None
            sym = None

    return (fullgraph, summary)


with open(shargs.mapfile, "rt") as file:
    fullgraph, summary = parse_file(file)

if shargs.fullgv:
    with open(shargs.fullgv, "w") as file:
        print(fullgraph.source, file=file)
if shargs.summarygv:
    with open(shargs.summarygv, "w") as file:
        print(summary.source, file=file)
