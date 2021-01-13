#ifndef GRAPHS_CPP_TOPOLOGICALSORT_H
#define GRAPHS_CPP_TOPOLOGICALSORT_H

#include <stack>
#include <PrintHelpers.h>
#include "EdgeWeightedDigraph.h"
#include "Cycle.h"

namespace internal {
    void topologicalSortRec(const EdgeWeightedDigraph& dg, const int v, // NOLINT
                            std::deque<bool>& visited, std::stack<int>& reversePostOrder) {
        visited[v] = true;
        for(const auto& edge : dg.adj(v)) {
            if(!visited[edge.to()]) {
                topologicalSortRec(dg, edge.to(), visited, reversePostOrder);
            }
        }
        reversePostOrder.push(v);
    }
}

// calculate a topological sort of digraph (reverse DFS postorder)
// digraph must be acyclic!
std::vector<int> topologicalSort(const EdgeWeightedDigraph& dg) {
    if(const auto cycle = containsCycle(dg); cycle) {
        std::cout<<std::flush;
        std::cerr<<"Digraph contains cycle - cannot do topological sort: ";
        print_vec(*cycle, "->", "\n", std::cerr);
        std::cerr<<std::flush;
        throw std::invalid_argument("Digraph must be acyclic");
    }

    std::deque<bool> visited(dg.V(), false);
    std::stack<int> reversePostOrder{};
    for(int v=0; v<dg.V(); ++v) {
        if(!visited[v]) {
            internal::topologicalSortRec(dg, v, visited, reversePostOrder);
        }
    }

    std::vector<int> result{};
    while(!reversePostOrder.empty()) {
        result.push_back(reversePostOrder.top());
        reversePostOrder.pop();
    }

    return result;
}



#endif //GRAPHS_CPP_TOPOLOGICALSORT_H
