#!/usr/bin/env python3

import pathlib
import argparse

import graphviz

parser = argparse.ArgumentParser()
parser.add_argument("-o", type=pathlib.Path, help="file to write the full graph to")
parser.add_argument(
    "-t", type=pathlib.Path, help="file to write the transitive graph to"
)
parser.add_argument(
    "logs",
    type=pathlib.Path,
    nargs="*",
    action="extend",
    help="list of log files to parse",
)

shargs = parser.parse_args()


def catfiles(files):
    for fn in files:
        with open(fn, "r") as file:
            yield from file


def parse_output(log):
    graph = graphviz.Digraph(
        strict=True, graph_attr=dict(overlap="False")
    )  # not transitive
    rootgraph = graphviz.Digraph(
        strict=True, graph_attr=dict(overlap="False")
    )  # transitive includes
    rootcause = None
    files = list()  # [(depth, header)...]
    for line in log:
        d, h = line.rstrip().split(" ", 1)
        d = d.count(".")
        h = pathlib.Path(h)

        if d == 0:
            rootcause = h
        else:
            """ "
            # A includes B.h, C.h
            .  A.h
            .. B.h
            .. C.h
            """
            while files[-1][0] >= d:
                del files[-1]

            # if str(h).startswith("..") :
            graph.edge(str(files[-1][1].parent), str(h.parent))
            rootgraph.edge(str(rootcause.parent), str(h.parent))

        files.append((d, h))

    return (graph, rootgraph)


graph, rootgraph = parse_output(catfiles(shargs.logs))

if shargs.o:
    with open(shargs.o, "w") as file:
        print(graph.source, file=file)
if shargs.t:
    with open(shargs.t, "w") as file:
        print(rootgraph.source, file=file)
