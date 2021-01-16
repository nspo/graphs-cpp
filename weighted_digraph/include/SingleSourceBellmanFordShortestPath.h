#ifndef GRAPHS_CPP_SINGLESOURCEBELLMANFORDSHORTESTPATH_H
#define GRAPHS_CPP_SINGLESOURCEBELLMANFORDSHORTESTPATH_H

#include "SingleSourceShortestPath.h"

class SingleSourceBellmanFordShortestPath : public SingleSourceShortestPath {
public:
    SingleSourceBellmanFordShortestPath(const EdgeWeightedDigraph &digraph, const int from) :
            SingleSourceShortestPath(digraph) {

        // Bellman-Ford: relax all edges V^2 times
        // optimization possible: keep queue of all vertices for which distancesTo[v] changed, and only iterate through
        //                        those in the next step
        distancesTo[from] = 0;

        for(int i=0; i < digraph.V(); ++i) {
            for(int v=0; v < digraph.V(); ++v) {
                for(const auto& edge : digraph.adj(v)) {
                    relax(edge);
                }
            }
        }

        // check for negative cycle
        for(int v=0; v < digraph.V(); ++v) {
            for(const auto& edge : digraph.adj(v)) {
                if (distancesTo[edge.to()] > distancesTo[edge.from()] + edge.weight()) {
                    // negative cycle
                    std::cout<<std::flush;
                    const int vStart = edge.from();
                    int vCyc = edgesTo[vStart]->from();
                    std::cerr<<"Negative cycle: "<<vStart;
                    while(vCyc != vStart) {
                        std::cerr<<", "<<vCyc;
                        vCyc = edgesTo[vCyc]->from();
                    }
                    std::cerr<<", "<<vStart<<"\n"<<std::flush;
                    throw std::invalid_argument(
                            "Bellman-Ford algorithm cannot find optimal " \
                            "solution as graph contains a cycle with negative weight!");
                }
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

#endif //GRAPHS_CPP_SINGLESOURCEBELLMANFORDSHORTESTPATH_H
