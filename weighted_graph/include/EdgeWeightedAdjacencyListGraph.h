#ifndef WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDADJACENCYLISTGRAPH_H
#define WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDADJACENCYLISTGRAPH_H

#include "EdgeWeightedGraph.h"

class EdgeWeightedAdjacencyListGraph : public EdgeWeightedGraph {
public:
    explicit EdgeWeightedAdjacencyListGraph(int numVertices)
            : numV(numVertices), numE(0), edgesByVertex(numVertices, std::vector<Edge>{}) {}

    explicit EdgeWeightedAdjacencyListGraph(std::istream& is) {
        if (!(is >> numV) || numV < 0) throw std::invalid_argument("Invalid format (V)");
        if (!(is >> numE || numE < 0)) throw std::invalid_argument("Invalid format (E)");
        edgesByVertex.insert(edgesByVertex.end(), numV, {});

        for (int i = 0; i < numE; ++i) {
            int v, w;
            double weight;
            if (!(is >> v >> w >> weight)) throw std::invalid_argument("Invalid format (edges)");
            if (v < 0 || v >= numV || w < 0 || w >= numV || std::isnan(weight) || !std::isfinite(weight)) {
                throw std::invalid_argument("Cannot create weighted edge v-w");
            }
            edgesByVertex[v].emplace_back(Edge(v, w, weight));
            edgesByVertex[w].emplace_back(Edge(v, w, weight));
        }
    }

    void addEdge(const Edge &e) override {
        const int v1 = e.either();
        const int v2 = e.other(v1);
        if(!validVertex(v1) || !validVertex(v2)) {
            throw std::invalid_argument("Vertex IDs invalid");
        }

        edgesByVertex[v1].emplace_back(e);
        edgesByVertex[v2].emplace_back(e);
        ++numE;
    }

    [[nodiscard]]
    const std::vector<Edge>& adj(int v) const override {
        if(!validVertex(v)) throw std::invalid_argument("Invalid vertex ID");
        return edgesByVertex[v];
    }

    // return edges (but skip duplicates)
    [[nodiscard]]
    std::vector<Edge> edges() const override {
        std::vector<Edge> result;
        result.reserve(numE);
        for (int i=0; static_cast<size_t>(i) < edgesByVertex.size(); ++i) {
            const auto& edgesVec = edgesByVertex[i];
            for(const auto& edge : edgesVec) {
                int other = edge.other(i);
                if (other < i) {
                    // skip already seen edges
                    continue;
                }
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
    std::vector<std::vector<Edge>> edgesByVertex {};

    [[nodiscard]]
    bool validVertex(int v) const {
        return v >= 0 && static_cast<size_t>(v) < edgesByVertex.size();
    }
};

#endif //WEIGHTED_GRAPHS_CPP_EDGEWEIGHTEDADJACENCYLISTGRAPH_H
