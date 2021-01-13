#ifndef WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDDIGRAPH_H
#define WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDDIGRAPH_H

#include <vector>
#include <ostream>
#include <cmath>
#include "DirectedEdge.h"

class EdgeWeightedDigraph {
public:
    // add edge to digraph
    virtual void addEdge(const DirectedEdge& e) = 0;

    // get all edges from vertex v
    [[nodiscard]]
    virtual const std::vector<DirectedEdge>& adj(int v) const = 0;

    // get all edges in graph
    [[nodiscard]]
    virtual std::vector<DirectedEdge> edges() const = 0;

    // get number of vertices
    [[nodiscard]]
    virtual int V() const = 0;

    // get number of edges
    [[nodiscard]]
    virtual int E() const = 0;

    // virtual destructor
    virtual ~EdgeWeightedDigraph() = default;
};

std::ostream& operator<<(std::ostream &os, const EdgeWeightedDigraph& graph) {
    os<<"EdgeWeightedDigraph (V="<<graph.V()<<", E="<<graph.E()<<")\n";
    for(int i=0; i<graph.V(); ++i) {
        os<<"Vertex "<<i<<": ";
        for(size_t idxEdge=0; idxEdge < graph.adj(i).size(); ++idxEdge) {
            const bool isLast = idxEdge == graph.adj(i).size() - 1;
            const auto& edge = graph.adj(i)[idxEdge];
            os<<"--"<<edge.weight()<<"-->("<<edge.to()<<")";
            if (!isLast) os << ", ";
        }
        os<<"\n";
    }
    os<<"\n";
    return os;
}


#endif //WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDDIGRAPH_H
