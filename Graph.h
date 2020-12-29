#ifndef GRAPHS_CPP_GRAPH_H
#define GRAPHS_CPP_GRAPH_H

#include <vector>
#include <sstream>

class Graph {
public:
    virtual void addEdge(int v, int w) = 0; // add edge v-w
    [[nodiscard]] virtual std::vector<int> adj(int v) const = 0; // get edges adjacent to v
    [[nodiscard]] virtual int V() const = 0; // number of vertices
    [[nodiscard]] virtual int E() const = 0; // number of edges
    [[nodiscard]] virtual std::string toString() const  = 0; // create string representation
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
    explicit AdjacencyListGraph(std::istream& is) {
        if(!(is >> numV) || numV < 0 ) throw std::invalid_argument("Invalid format (V)");
        if(!(is >> numE || numE < 0)) throw std::invalid_argument("Invalid format (E)");
        vertices.insert(vertices.end(), numV, {});
        for(int i=0; i<numE; ++i) {
            int v1, v2;
            if(!(is >> v1 >> v2)) throw std::invalid_argument("Invalid format (edges)");
            if(!vertexValid(v1) || !vertexValid(v2)) {
                throw std::invalid_argument("Cannot create edge v1-v2");
            }
            vertices[v1].push_back(v2);
            vertices[v2].push_back(v1);
        }
    }

    void addEdge(int v, int w) override {
        if(!vertexValid(v) || !vertexValid(w)) {
            throw std::invalid_argument("Cannot create edge v-w");
        }
        vertices[v].push_back(w);
        vertices[w].push_back(v);
        ++numE;
    }

    [[nodiscard]] std::vector<int> adj(int v) const override {
        if(!vertexValid(v)) {
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
        for(size_t i=0; i<vertices.size(); ++i) {
            for(const auto edge : vertices[i]) {
                ss<<i<<"-"<<edge<<"\n";
            }
        }
        return ss.str();
    }

private:
    int numV = 0; // vertices
    int numE = 0; // edges
    std::vector<std::vector<int>> vertices {}; // vector with V elements each of size degree(vertex) to represent edges

    [[nodiscard]] bool vertexValid(int v) const {
        return v >= 0 && v < numV;
    }
};

#endif //GRAPHS_CPP_GRAPH_H
