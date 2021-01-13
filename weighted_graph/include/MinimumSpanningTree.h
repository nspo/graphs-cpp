#ifndef WEIGHTED_GRAPHS_CPP_MINIMUMSPANNINGTREE_H
#define WEIGHTED_GRAPHS_CPP_MINIMUMSPANNINGTREE_H

#include "EdgeWeightedGraph.h"
#include "DisjointSets.h"
#include <unordered_set>
#include <algorithm>
#include <queue>

template <typename T>
using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<>>;

// Find a https://en.wikipedia.org/wiki/Minimum_spanning_tree (or forest)
// with Kruskal's algorithm (https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)
class MinimumSpanningTree {
public:

    explicit MinimumSpanningTree(const EdgeWeightedGraph& graph) {
        if(graph.V() < 1) throw std::invalid_argument("Graph must contain at least one vertex");

        tree.reserve(graph.V()-1);

        // create minimum priority queue of edges (i.e. ascending weights)
        auto edges = graph.edges();
        min_priority_queue<Edge> edges_minPQ(edges.begin(), edges.end()); // building heap takes O(E) time

        // add edges to tree unless doing this would create a cycle (until N=V-1)
        DisjointSets uf(graph.V()); // O(V)
        while(tree.size() < static_cast<size_t>(graph.V()-1)) { // O(E) iterations
            if (edges_minPQ.empty()) throw std::invalid_argument("Could not create MST from graph");

            const auto currMinEdge = edges_minPQ.top(); // edge with minimal weight
            edges_minPQ.pop(); // O(log(E))

            // check whether adding this would create a cycle
            const int v1 = currMinEdge.either();
            const int v2 = currMinEdge.other(v1);
            if (!uf.connected(v1, v2)) {  // O(log*(V)) - nearly constant time op
                // would not create a cycle - matches O(V) times in total
                uf.setUnion(v1, v2); // O(log*(V))
                tree.push_back(currMinEdge);
                mst_weight += currMinEdge.getWeight();
            }
        }
    }

    [[nodiscard]]
    const std::vector<Edge>& edges() const {
        return tree;
    }

    [[nodiscard]]
    double weight() const {
        return mst_weight;
    }

private:
    std::vector<Edge> tree;
    double mst_weight = 0;
};

#endif //WEIGHTED_GRAPHS_CPP_MINIMUMSPANNINGTREE_H
