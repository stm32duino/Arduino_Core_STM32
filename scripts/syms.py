#!/usr/bin/env python3

import pathlib
import sys
try :
    import graphviz
except :
    print("This script requires the graphviz module to run.")
    print("Please install it with:")
    print("`pip install graphviz`")
    exit(1)

if len(sys.argv) != 4 :
    print("Usage: ./syms.py <mapfile> <output_fullgraph> <output_summary>")
    exit(1)

mapfile = pathlib.Path(sys.argv[1])
fullgraphfile = pathlib.Path(sys.argv[2])
summaryfile = pathlib.Path(sys.argv[3])

if not (mapfile.exists() and mapfile.is_file()) :
    print("Can't find file", mapfile)
    exit(1)


def parse_file(mapf) :
    fullgraph = graphviz.Digraph(graph_attr=dict(overlap="False"))
    summary = graphviz.Digraph(strict=True, graph_attr=dict(overlap="False"))

    start = "Archive member included to satisfy reference by file (symbol)"
    stop = "Discarded input sections"
    for line in mapf :
        if line.startswith(start) :
            break

    provider = None
    demander = None
    sym = None
    for line in mapf :
        if line.isspace() :
            continue
        if line.startswith(stop) :
            break

        if line.startswith((" ", "\t")) :
            try :
                demander, sym = line.strip().rsplit(") (", 1)
                demander = demander + ")"
                sym = "("+sym
            except :
                continue
        else :
            provider = line.strip()

        if provider and demander and sym :
            objdemander = demander.rsplit("/", 1)[1] # .split("(")[0] gets the lib ; without this you get the obj
            objprovider = provider.rsplit("/", 1)[1]
            libdemander = objdemander.split("(")[0]
            libprovider = objprovider.split("(")[0]

            fullgraph.edge(objdemander, objprovider, tooltip=sym)
            summary.edge(libdemander, libprovider)

            provider = None
            demander = None
            sym = None

    return (fullgraph, summary)


with open(mapfile, "rt") as file :
    fullgraph, summary = parse_file(file)


with open(fullgraphfile, "w") as file :
    print(fullgraph.source, file=file)
with open(summaryfile, "w") as file :
    print(summary.source, file=file)
