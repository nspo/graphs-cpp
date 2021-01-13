#!/usr/bin/env python3

import networkx as nx
from matplotlib import pyplot as plt
import argparse

parser = argparse.ArgumentParser()
parser.add_argument(
    dest="digraph_file",
    help="Text file weighted digraph"
)
parser.add_argument(
    "--weights", "-w",
    action="store_true",
    default=False,
    help="Draw edge weights")

args = parser.parse_args()

# read digraph

infile = open(args.digraph_file, "r")
numVertices = int(infile.readline())
numEdges = int(infile.readline())
G = nx.DiGraph()


for i in range(0, numEdges):
    line = infile.readline()
    split_line =  line.split(" ")

    fromVertex, toVertex, edgeWeight = int(split_line[0]), int(split_line[1]), float(split_line[2])
    G.add_edge(fromVertex, toVertex, weight=edgeWeight)

# add vertices (to make those without edges are also shown)
for v in range(0, numVertices):
    G.add_node(v)

infile.close()

# draw digraph

if nx.check_planarity(G):
    layout = nx.planar_layout(G)
else:
    layout = nx.spring_layout(G)

nx.draw(G, layout, node_size=700)
nx.draw_networkx_labels(G, pos=layout, font_size=15, font_color="white",  font_family="sans-serif")

if args.weights:
    labels = nx.get_edge_attributes(G, "weight")
    nx.draw_networkx_edge_labels(G, pos=layout, edge_labels=labels)

plt.show()
