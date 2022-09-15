#!/usr/bin/env python3

import sys
import pathlib
try :
    import graphviz
except :
    print("This script requires the graphviz module to run.")
    print("Please install it with:")
    print("`pip install graphviz`")
    exit(1)


def catfiles(files) :
    for fn in files :
        with open(fn, "r") as file :
            yield from file

def parse_output(log) :
    graph = graphviz.Digraph(strict=True, graph_attr=dict(overlap="False")) # not transitive
    rootgraph = graphviz.Digraph(strict=True, graph_attr=dict(overlap="False")) # transitive includes
    rootcause = None
    files = list() # [(depth, header)...]
    for line in log :
        d, h = line.rstrip().split(" ", 1)
        d = d.count(".")
        h = pathlib.Path(h)

        if d == 0 :
            rootcause = h
        else :
            """"
            # A includes B.h, C.h
            .  A.h
            .. B.h
            .. C.h
            """
            while files[-1][0] >= d :
                del files[-1]

            # if str(h).startswith("..") :
            graph.edge(str(files[-1][1].parent), str(h.parent))
            rootgraph.edge(str(rootcause.parent), str(h.parent))

        files.append((d, h))

    return (graph, rootgraph)

if len(sys.argv) < 4 :
    print("Usage: ./includes.py <outfile> <outfile_transitive> <logfiles...>")
    exit(1)

outfiles = (pathlib.Path(sys.argv[1]), pathlib.Path(sys.argv[2]))
infiles = sys.argv[3:]
graph, rootgraph = parse_output(catfiles(infiles))

with open(outfiles[0], "w") as file :
    print(graph.source, file=file)
with open(outfiles[1], "w") as file :
    print(rootgraph.source, file=file)
