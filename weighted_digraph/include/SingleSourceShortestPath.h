#ifndef WEIGHTED_GRAPHS_CPP_SINGLESOURCESHORTESTPATH_H
#define WEIGHTED_GRAPHS_CPP_SINGLESOURCESHORTESTPATH_H

#include <queue>
#include <algorithm>
#include "EdgeWeightedDigraph.h"
#include "PriorityQueue.h"
#include "IndexedPriorityQueue.h"

class SingleSourceShortestPath {
public:
    SingleSourceShortestPath() = delete;

    [[nodiscard]]
    double distTo(const int to) const {
        checkIndex(to);
        return distancesTo[to];
    }

    [[nodiscard]]
    std::vector<DirectedEdge> pathTo(const int to) const {
        checkIndex(to);
        std::vector<DirectedEdge> result;
        int v = to;
        // add vertices in reverse order
        while (edgesTo[v]) {
            // edge to v was found
            result.emplace_back(*edgesTo[v]);
            v = edgesTo[v]->from();
        }
        std::reverse(result.begin(), result.end()); // put result into correct order
        return result;
    }

    [[nodiscard]]
    bool hasPathTo(const int to) const {
        checkIndex(to);
        return std::isfinite(distancesTo[to]);
    }

protected:
    std::vector<std::optional<DirectedEdge>> edgesTo; // edge used to step to this vertex
    std::vector<double> distancesTo; // distance from start to this vertex

    explicit SingleSourceShortestPath(const EdgeWeightedDigraph& digraph) :
            edgesTo(digraph.V(), std::nullopt),
            distancesTo(digraph.V(), std::numeric_limits<double>::infinity() // inf distance by default
            ) {}

    void checkIndex(const int v) const {
        if (v < 0 || static_cast<size_t>(v) >= edgesTo.size()) {
            throw std::invalid_argument("Invalid index");
        }
    }
};

#endif //WEIGHTED_GRAPHS_CPP_SINGLESOURCESHORTESTPATH_H
