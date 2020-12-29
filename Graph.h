#ifndef GRAPHS_CPP_GRAPH_H
#define GRAPHS_CPP_GRAPH_H

#include <vector>
#include <sstream>
#include <algorithm>

namespace graph {

    class Graph {
    public:
        virtual void addEdge(int v, int w) = 0; // add edge v-w
        [[nodiscard]] virtual const std::vector<int>& adj(int v) const = 0; // get edges adjacent to v
        [[nodiscard]] virtual int V() const = 0; // number of vertices
        [[nodiscard]] virtual int E() const = 0; // number of edges
        [[nodiscard]] virtual std::string toString() const = 0; // create string representation
        [[nodiscard]] virtual bool vertexValid(int v) const = 0; // whether a vertex exists
        virtual ~Graph() = default; // virtual destructor
    };

    class AdjacencyListGraph : public Graph {
    public:
        // create graph with V vertices
        explicit AdjacencyListGraph(int V) :
                numV(V),
                numE(0),
                vertices(V, std::vector<int>{}) {}

        // create graph with input stream
        explicit AdjacencyListGraph(std::istream &is) {
            if (!(is >> numV) || numV < 0) throw std::invalid_argument("Invalid format (V)");
            if (!(is >> numE || numE < 0)) throw std::invalid_argument("Invalid format (E)");
            vertices.insert(vertices.end(), numV, {});
            for (int i = 0; i < numE; ++i) {
                int v1, v2;
                if (!(is >> v1 >> v2)) throw std::invalid_argument("Invalid format (edges)");
                if (v1 < 0 || v1 >= numV || v2 < 0 || v2 >= numV) {
                    throw std::invalid_argument("Cannot create edge v1-v2");
                }
                vertices[v1].push_back(v2);
                vertices[v2].push_back(v1);
            }
        }

        void addEdge(int v, int w) override {
            if (!vertexValid(v) || !vertexValid(w)) {
                throw std::invalid_argument("Cannot create edge v-w");
            }
            vertices[v].push_back(w);
            vertices[w].push_back(v);
            ++numE;
        }

        [[nodiscard]] const std::vector<int>& adj(int v) const override {
            if (!vertexValid(v)) {
                throw std::invalid_argument("Invalid vertex");
            }
            return vertices[v];
        }

        [[nodiscard]] int V() const override {
            return numV;
        }

        [[nodiscard]] int E() const override {
            return numE;
        }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "[Graph with " << numV << " vertices and " << numE << " edges]\n";
            for (size_t i = 0; i < vertices.size(); ++i) {
                for (const auto edge : vertices[i]) {
                    ss << i << "-" << edge << "\n";
                }
            }
            return ss.str();
        }

        [[nodiscard]] bool vertexValid(int v) const override {
            return v >= 0 && v < numV;
        }

    private:
        int numV = 0; // vertices
        int numE = 0; // edges
        std::vector<std::vector<int>> vertices{}; // vector with V elements each of size degree(vertex) to represent edges

    };

    // degree of a vertex
    int degree(const Graph& g, const int v) {
        if(!g.vertexValid(v)) throw std::invalid_argument("Invalid vertex");
        return g.adj(v).size();
    }

    // maximum degree of any vertex in graph
    int maxDegree(const Graph& g) {
        int deg = 0;
        for(int i=0; i<g.V(); ++i) {
            deg = std::max(deg, static_cast<int>(g.adj(i).size()));
        }

        return deg;
    }

    // average degree of vertices
    double avgDegree(const Graph& g) {
        return 2.0 * g.E() / g.V();
    }

    // count the number of self-loops
    int numSelfLoops(const Graph& g) {
        int num = 0;
        for(int i=0; i<g.V(); ++i) {
            for(const auto& e : g.adj(i)) {
                if(e == i) ++num;
            }
        }
        return num/2; // each self-loop is counted twice
    }

    // Depth First Search for paths starting at a specific vertex
    class PathsFromDFS {
    public:
        explicit PathsFromDFS(const Graph &g, const int _start) :
                start {_start}, marked(g.V(), false), edgeTo(g.V(), -1) {
            dfs(g, start, -1);
        }

        [[nodiscard]] bool hasPathTo(int v) const {
            if(!validVertex(v)) {
                return false;
            } else {
                return marked[v];
            }
        }

        [[nodiscard]] std::vector<int> pathTo(const int v) const {
            if(!hasPathTo(v)) {
                return {};
            }

            // build path in the reverse direction
            std::vector<int> path{v};
            int prev = edgeTo[v];
            while(prev != -1) {
                path.push_back(prev);
                prev = edgeTo[prev];
            }

            std::reverse(path.begin(), path.end());
            return path;
        }

    private:
        const int start; // from which vertex the search started
        std::vector<bool> marked; // whether a vertex was already visited
        std::vector<int> edgeTo; // from which vertex another vertex was visited from the first time

        void dfs(const Graph& g, const int v, const int fromV) {
            marked[v] = true; // mark as visited
            edgeTo[v] = fromV; // save that we got to v from fromV
            for(const int other : g.adj(v)) {
                if(!marked[other]) {
                    dfs(g, other, v);
                }
            }
        }

        [[nodiscard]] bool validVertex(const int v) const {
            if(v < 0 || static_cast<size_t>(v) >= marked.size()) {
                return false;
            } else {
                return true;
            }
        }
    };

} // namespace graph

#endif //GRAPHS_CPP_GRAPH_H
