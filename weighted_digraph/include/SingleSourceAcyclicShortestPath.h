#ifndef GRAPHS_CPP_SINGLESOURCEACYCLICSHORTESTPATH_H
#define GRAPHS_CPP_SINGLESOURCEACYCLICSHORTESTPATH_H

#include "SingleSourceShortestPath.h"
#include "TopologicalSort.h"

class SingleSourceAcyclicShortestPath : public SingleSourceShortestPath {
public:
    SingleSourceAcyclicShortestPath(const EdgeWeightedDigraph &digraph, const int from) :
            SingleSourceShortestPath(digraph) {

        // Shortest paths for DAGs
        distancesTo[from] = 0;

        for(const int v : topologicalSort(digraph)) {
            for(const auto& edge : digraph.adj(v)) {
                relax(edge);
            }
        }
    }

private:
    // make use of edge if it gives the shortest path so far to e.to()
    void relax(const DirectedEdge& e) {
        const int from = e.from();
        const int to = e.to();
        if (distancesTo[to] > distancesTo[from] + e.weight()) {
            // use edge
            distancesTo[to] = distancesTo[from] + e.weight();
            edgesTo[to] = e;
        }
    }
};

#endif //GRAPHS_CPP_SINGLESOURCEACYCLICSHORTESTPATH_H
