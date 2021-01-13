#ifndef GRAPHS_CPP_CYCLE_H
#define GRAPHS_CPP_CYCLE_H

#include "EdgeWeightedDigraph.h"

namespace internal {
    bool containsCycleRec(const EdgeWeightedDigraph& dg, const int v, std::deque<bool>& visited,
                          std::vector<int>& edgeTo,
                          std::unordered_set<int>& onStack, std::stack<int>& cycle) {
        onStack.insert(v);
        for(const auto& edge : dg.adj(v)) {
            const int other = edge.to();
            if (!visited[other]) {
                visited[other] = true;
                edgeTo[other] = v;
                onStack.insert(other);
                if(containsCycleRec(dg, other, visited, edgeTo, onStack, cycle)) {
                    return true;
                }
            } else if(onStack.find(other) != onStack.end()) {
                // other is already visited AND on stack -> cycle
                // save cycle
                for(int x=v; x != other; x = edgeTo[x]) {
                    cycle.push(x);
                }
                cycle.push(other);
                cycle.push(v);
                return true;
            }
        }
        onStack.erase(v);
        return false;
    }
}

// check whether digraph contains a cycle
// returns cycle or nothing
std::optional<std::vector<int>> containsCycle(const EdgeWeightedDigraph& dg) {
    std::deque<bool> visited(dg.V(), false);
    std::vector<int> edgeTo(dg.V(), -1);
    std::unordered_set<int> onStack{}; // whether a node is currently on the stack
    std::stack<int> cycle{}; // cycle (if one exists)
    // loop through a vertices
    bool cycleFound = false;
    for(int v=0; v < dg.V(); ++v) {
        if(!visited[v]) {
            visited[v] = true;
            if(internal::containsCycleRec(dg, v, visited, edgeTo, onStack, cycle)) {
                cycleFound = true;
                break;
            }
        }
        onStack.clear(); // clear onStack as the next recursion will be for a new connected component
    }

    if(cycleFound) {
        std::vector<int> cycleVec{};
        while(!cycle.empty()) {
            cycleVec.push_back(cycle.top());
            cycle.pop();
        }
        return {cycleVec};
    } else {
        return {};
    }
}

#endif //GRAPHS_CPP_CYCLE_H
