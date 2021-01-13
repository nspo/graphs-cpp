#ifndef DIGRAPHS_CPP_DIGRAPH_H
#define DIGRAPHS_CPP_DIGRAPH_H

#include <vector>
#include <memory>
#include <sstream>
#include <deque>
#include <unordered_set>
#include <stack>
#include "PrintHelpers.h"

namespace digraph {

    // Interface of a directed graph
    class Digraph {
    public:
        virtual void addEdge(int v, int w) = 0; // add edge v->w to graph
        [[nodiscard]] virtual const std::vector<int> &adj(int v) const = 0; // get vertices adjacent to v
        [[nodiscard]] virtual int V() const = 0; // number of vertices
        [[nodiscard]] virtual int E() const = 0; // number of edges
        [[nodiscard]] virtual std::unique_ptr<Digraph> reverse() const = 0; // reverse of this digraph
        [[nodiscard]] virtual std::string toString() const = 0; // create string representation
        [[nodiscard]] virtual bool vertexValid(int v) const = 0; // whether a vertex exists
        virtual ~Digraph() = default; // virtual destructor
    };

    // Graph built with adjacency list
    class AdjacencyListDigraph : public Digraph {
    public:
        // create graph with V vertices
        explicit AdjacencyListDigraph(int V) :
                numV(V),
                numE(0),
                adjacencies(V, std::vector<int> {}) {}

        // create graph with input stream
        explicit AdjacencyListDigraph(std::istream &is) {
            if (!(is >> numV) || numV < 0) throw std::invalid_argument("Invalid format (V)");
            if (!(is >> numE || numE < 0)) throw std::invalid_argument("Invalid format (E)");
            adjacencies.insert(adjacencies.end(), numV, {});
            for (int i = 0; i < numE; ++i) {
                int v, w;
                if (!(is >> v >> w)) throw std::invalid_argument("Invalid format (edges)");
                if (v < 0 || v >= numV || w < 0 || w >= numV) {
                    throw std::invalid_argument("Cannot create edge v->w");
                }
                adjacencies[v].push_back(w);
            }
        }

        // add edge v->w to graph
        void addEdge(int v, int w) override {
            if (!vertexValid(v) || !vertexValid(w)) {
                throw std::invalid_argument("Cannot create edge v-w");
            }
            adjacencies[v].push_back(w);
            ++numE;
        }

        // get vertices adjacent to v
        [[nodiscard]] const std::vector<int> &adj(int v) const override {
            if (!vertexValid(v)) {
                throw std::invalid_argument("Invalid vertex");
            }
            return adjacencies[v];
        }

        // number of vertices
        [[nodiscard]] int V() const override {
            return numV;
        }

        // number of edges
        [[nodiscard]] int E() const override {
            return numE;
        }

        // reverse of this digraph
        [[nodiscard]] std::unique_ptr<Digraph> reverse() const override {
            std::unique_ptr<Digraph> rdg = std::make_unique<AdjacencyListDigraph>(this->V());
            for(int from=0; from < this->V(); ++from) {
                for(const int to : this->adj(from)) {
                    rdg->addEdge(to, from); // add reverse edge
                }
            }
            return rdg;
        }

        // create string representation
        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "[Digraph with " << numV << " vertices and " << numE << " edges]\n";
            for (size_t i = 0; i < adjacencies.size(); ++i) {
                for (const auto edge : adjacencies[i]) {
                    ss << i << "->" << edge << "\n";
                }
            }
            return ss.str();
        }

        // whether a vertex exists
        [[nodiscard]] bool vertexValid(int v) const override {
            return v >= 0 && v < numV;
        }

    private:
        int numV = 0; // vertices
        int numE = 0; // edges
        std::vector <std::vector<int>> adjacencies{}; // vector with V elements each of size outDegree(vertex) to represent edges

    };

    namespace internal {
        bool containsCycleRec(const Digraph& dg, const int v, std::deque<bool>& visited,
                              std::vector<int>& edgeTo,
                              std::unordered_set<int>& onStack, std::stack<int>& cycle) {
            onStack.insert(v);
            for(const int other : dg.adj(v)) {
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
    std::optional<std::vector<int>> containsCycle(const Digraph& dg) {
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

    namespace internal {
        void topologicalSortRec(const Digraph& dg, const int v,
                                std::deque<bool>& visited, std::stack<int>& reversePostOrder) {
            visited[v] = true;
            for(const int other : dg.adj(v)) {
                if(!visited[other]) {
                    topologicalSortRec(dg, other, visited, reversePostOrder);
                }
            }
            reversePostOrder.push(v);
        }
    }

    // calculate a topological sort of digraph (reverse DFS postorder)
    // digraph must be acyclic!
    std::vector<int> topologicalSort(const Digraph& dg) {
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

    // calculates strongly connected components (each node reachable from each node) with Kosaraju-Sharir algorithm
    class StronglyConnectedComponents {
    public:
        explicit StronglyConnectedComponents(const Digraph& dg) : compId(dg.V(), -1), numComp{0} {
            const auto pReverse = dg.reverse();
            // (1) calculate reverse postorder of reverse digraph with DFS
            std::stack<int> reversePostorder;
            std::deque<bool> visited(pReverse->V(), false);
            for(int i=0; i < pReverse->V(); ++i) {
                if(!visited[i]) {
                    dfsReverseGraph(*pReverse, i, visited, reversePostorder);
                }
            }

            // (2) run DFS in (non-reverse) digraph with order given by reversePostorder
            std::fill(visited.begin(), visited.end(), false);
            std::vector<int> edgeTo(dg.V(), -1);
            while(!reversePostorder.empty()) {
                const int v = reversePostorder.top();
                reversePostorder.pop();
                if (!visited[v]) {
                    compId[v] = numComp;
                    dfsNormalGraph(dg, v, visited, edgeTo);
                    ++numComp;
                }
            }
        }

        [[nodiscard]] int numberOfComponents() const {
            return numComp;
        }

        // whether v and w are strongly connected
        [[nodiscard]] bool stronglyConnected(const int v, const int w) const {
            if(v < 0 || static_cast<size_t>(v) >= compId.size() || w < 0 || static_cast<size_t>(w) >= compId.size()) {
                throw std::invalid_argument("invalid vertex IDs");
            }
            return compId[v] == compId[w];
        }

        // all vertices per component
        [[nodiscard]] std::vector<std::vector<int>> components() const {
            std::vector<std::vector<int>> result(numComp, std::vector<int>{});
            for(size_t v=0; v<compId.size(); ++v) {
                result[compId[v]].push_back(v);
            }
            return result;
        }

    private:
        std::vector<int> compId; // ID of strong component for each vertex
        int numComp; // number of strong components

        // DFS for reverse digraph to calculate reverse postorder
        static void dfsReverseGraph(const Digraph& reverseDg, const int v, std::deque<bool>& visited, std::stack<int>& reversePostorder) {
            visited[v] = true;
            for(const int other : reverseDg.adj(v)) {
                if(!visited[other]) {
                    dfsReverseGraph(reverseDg, other, visited, reversePostorder);
                }
            }
            reversePostorder.push(v);
        }

        // DFS for normal digraph to calculate strong components
        void dfsNormalGraph(const Digraph& dg, const int v, std::deque<bool>& visited, std::vector<int>& edgeTo) {
            visited[v] = true;
            for(const int other : dg.adj(v)) {
                if(!visited[other]) {
                    edgeTo[other] = v;
                    compId[other] = compId[v];
                    dfsNormalGraph(dg, other, visited, edgeTo);
                }
            }
        }
    };

}

#endif //DIGRAPHS_CPP_DIGRAPH_H
