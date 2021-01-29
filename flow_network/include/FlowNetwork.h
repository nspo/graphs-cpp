#ifndef WEIGHTED_GRAPHS_CPP_FLOWNETWORK_H
#define WEIGHTED_GRAPHS_CPP_FLOWNETWORK_H

#include <vector>
#include <ostream>
#include <cmath>
#include "FlowEdge.h"
#include <memory>

class FlowNetwork {
public:
    // add edge to digraph
    virtual void addEdge(const FlowEdge& e) = 0;

    // get all forward and backward edges from vertex v
    [[nodiscard]]
    virtual const std::vector<std::shared_ptr<FlowEdge>>& adj(int v) const = 0;

    // get all edges in network
    [[nodiscard]]
    virtual std::vector<std::shared_ptr<FlowEdge>> edges() const = 0;

    // get number of vertices
    [[nodiscard]]
    virtual int V() const = 0;

    // get number of edges
    [[nodiscard]]
    virtual int E() const = 0;

    // virtual destructor
    virtual ~FlowNetwork() = default;
};

std::ostream& operator<<(std::ostream &os, const FlowNetwork& graph) {
    os<<"FlowNetwork (V="<<graph.V()<<", E="<<graph.E()<<")\n";
    for(int i=0; i<graph.V(); ++i) {
        os<<"Vertex "<<i<<": ";
        for(size_t idxEdge=0; idxEdge < graph.adj(i).size(); ++idxEdge) {
            const bool isLast = idxEdge == graph.adj(i).size() - 1;
            const auto& edge = graph.adj(i)[idxEdge];
            os<<*edge;
            if (!isLast) os << ", ";
        }
        os<<"\n";
    }
    os<<"\n";
    return os;
}


#endif //WEIGHTED_GRAPHS_CPP_FLOWNETWORK_H
