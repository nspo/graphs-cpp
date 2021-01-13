#ifndef WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDADJACENCYLISTDIGRAPH_H
#define WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDADJACENCYLISTDIGRAPH_H

#include "EdgeWeightedDigraph.h"

class EdgeWeightedAdjacencyListDigraph : public EdgeWeightedDigraph {
public:
    explicit EdgeWeightedAdjacencyListDigraph(int numVertices)
            : numV(numVertices), numE(0), edgesByVertex(numVertices, std::vector<DirectedEdge>{}) {}

    explicit EdgeWeightedAdjacencyListDigraph(std::istream& is) {
        if (!(is >> numV) || numV < 0) throw std::invalid_argument("Invalid format (V)");
        if (!(is >> numE || numE < 0)) throw std::invalid_argument("Invalid format (E)");
        edgesByVertex.insert(edgesByVertex.end(), numV, {});

        for (int i = 0; i < numE; ++i) {
            int fromVertex, toVertex;
            double weight;
            if (!(is >> fromVertex >> toVertex >> weight)) throw std::invalid_argument("Invalid format (edges)");
            if (fromVertex < 0 || fromVertex >= numV || toVertex < 0 || toVertex >= numV || std::isnan(weight) || !std::isfinite(weight)) {
                throw std::invalid_argument("Cannot create weighted edge v->w");
            }
            edgesByVertex[fromVertex].emplace_back(DirectedEdge(fromVertex, toVertex, weight));
        }
    }

    void addEdge(const DirectedEdge &e) override {
        const int vertexFrom = e.from();
        const int vertexTo = e.to();
        if(!validVertex(vertexFrom) || !validVertex(vertexTo)) {
            throw std::invalid_argument("Vertex IDs invalid");
        }

        edgesByVertex[vertexFrom].emplace_back(e);
        ++numE;
    }

    [[nodiscard]]
    const std::vector<DirectedEdge>& adj(int v) const override {
        if(!validVertex(v)) throw std::invalid_argument("Invalid vertex ID");
        return edgesByVertex[v];
    }

    [[nodiscard]]
    std::vector<DirectedEdge> edges() const override {
        std::vector<DirectedEdge> result;
        result.reserve(numE);
        for (const auto& edgesVec : edgesByVertex) {
            for(const auto& edge : edgesVec) {
                result.emplace_back(edge);
            }
        }

        return result;
    }

    [[nodiscard]]
    int V() const override {
        return numV;
    }

    [[nodiscard]]
    int E() const override {
        return numE;
    }

private:
    int numV {};
    int numE {};
    std::vector<std::vector<DirectedEdge>> edgesByVertex {};

    [[nodiscard]]
    bool validVertex(int v) const {
        return v >= 0 && static_cast<size_t>(v) < edgesByVertex.size();
    }
};

#endif //WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDADJACENCYLISTDIGRAPH_H
