#ifndef WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDGRAPH_H
#define WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDGRAPH_H

#include <vector>
#include <ostream>
#include <cmath>
#include "Edge.h"

class EdgeWeightedGraph {
public:
    // add edge to graph
    virtual void addEdge(const Edge& e) = 0;

    // get all edges from vertex v
    [[nodiscard]]
    virtual const std::vector<Edge>& adj(int v) const = 0;

    // get all edges in graph
    [[nodiscard]]
    virtual std::vector<Edge> edges() const = 0;

    // get number of vertices
    [[nodiscard]]
    virtual int V() const = 0;

    // get number of edges
    [[nodiscard]]
    virtual int E() const = 0;

    // virtual destructor
    virtual ~EdgeWeightedGraph() = default;
};

std::ostream& operator<<(std::ostream &os, const EdgeWeightedGraph& graph) {
    os<<"EdgeWeightedGraph (V="<<graph.V()<<", E="<<graph.E()<<")\n";
    for(int i=0; i<graph.V(); ++i) {
        os<<"Vertex "<<i<<": ";
        for(size_t idxEdge=0; idxEdge < graph.adj(i).size(); ++idxEdge) {
            const bool last = idxEdge == graph.adj(i).size()-1;
            const auto& edge = graph.adj(i)[idxEdge];
            os<<"--"<<edge.getWeight()<<"--("<<edge.other(i)<<")";
            if (!last) os<<", ";
        }
        os<<"\n";
    }
    os<<"\n";
    return os;
}


#endif //WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDGRAPH_H
