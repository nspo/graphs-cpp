#ifndef GRAPHS_CPP_FORDFULKERSON_H
#define GRAPHS_CPP_FORDFULKERSON_H

#include <deque>
#include <queue>
#include "FlowNetwork.h"

// Ford-Fulkerson algorithm for min-cut/max-flow problem
class FordFulkerson {
public:

    FordFulkerson(const FlowNetwork& fn, const int s, const int t) {
        value = 0.0;
        while (hasAugmentingPath(fn, s, t)) {
            double bottleneck = std::numeric_limits<double>::infinity();
            for (int v=t; v != s; v = edgeTo[v]->other(v)) {
                bottleneck = std::min(bottleneck, edgeTo[v]->residualCapacityTo(v));
            }
            for (int v=t; v!= s; v = edgeTo[v]->other(v)) {
                edgeTo[v]->addResidualFlowTo(v, bottleneck);
            }
            value += bottleneck;
        }
    }

    [[nodiscard]]
    double getValue() const {
        return value;
    }

    [[nodiscard]]
    bool isInCut(const int v) const {
        return v >= 0 && static_cast<size_t>(v) < marked.size() && marked[v];
    }

    [[nodiscard]]
    bool hasAugmentingPath(const FlowNetwork& fn, const int s, const int t) {
        edgeTo.clear();
        edgeTo.insert(edgeTo.begin(), fn.V(), {});
        marked.clear();
        marked.insert(marked.begin(), fn.V(), false);

        std::queue<int> queue{};
        queue.push(s);
        marked[s] = true;
        while (!queue.empty()) {
            const int v = queue.front();
            queue.pop();
            for (const auto& edge : fn.adj(v)) {
                const int w = edge->other(v);
                if (edge->residualCapacityTo(w) > 0 && !marked[w]) {
                    edgeTo[w] = edge;
                    marked[w] = true;
                    queue.push(w);
                }
            }
        }
        return marked[t];
    }
private:
    std::deque<bool> marked; // if path from start to v is in residual network
    std::vector<std::shared_ptr<FlowEdge>> edgeTo; // from which vertex to get to v
    double value; // max flow value
};
#endif //GRAPHS_CPP_FORDFULKERSON_H
