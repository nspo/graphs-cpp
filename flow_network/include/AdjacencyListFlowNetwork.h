#ifndef WEIGHTED_GRAPHS_CPP_ADJACENCYLISTFLOWNETWORK_H
#define WEIGHTED_GRAPHS_CPP_ADJACENCYLISTFLOWNETWORK_H

#include <istream>
#include "FlowNetwork.h"

class AdjacencyListFlowNetwork : public FlowNetwork {
public:
    explicit AdjacencyListFlowNetwork(const int numVertices)
            : numV(numVertices), numE(0), edgesByVertex(numVertices, std::vector<std::shared_ptr<FlowEdge>>{}) {}

    explicit AdjacencyListFlowNetwork(std::istream& is) {
        if (!(is >> numV) || numV < 0) throw std::invalid_argument("Invalid format (V)");
        if (!(is >> numE || numE < 0)) throw std::invalid_argument("Invalid format (E)");
        edgesByVertex.insert(edgesByVertex.end(), numV, {});

        for (int i = 0; i < numE; ++i) {
            int fromVertex, toVertex;
            double capacity;
            if (!(is >> fromVertex >> toVertex >> capacity)) throw std::invalid_argument("Invalid format (edges)");
            if (fromVertex < 0 || fromVertex >= numV || toVertex < 0 || toVertex >= numV || capacity <= 0 || !std::isfinite(capacity)) {
                throw std::invalid_argument("Cannot create flow edge v->w");
            }
            edgesByVertex[fromVertex].emplace_back(std::make_shared<FlowEdge>(fromVertex, toVertex, capacity));
            edgesByVertex[toVertex].emplace_back(edgesByVertex[fromVertex].back());
        }
    }

    void addEdge(const FlowEdge& e) override {
        const int fromVertex = e.from();
        const int toVertex = e.to();
        if(!validVertex(fromVertex) || !validVertex(toVertex)) {
            throw std::invalid_argument("Vertex IDs invalid");
        }
        if (e.capacity() < 0 || !std::isfinite(e.capacity())) {
            throw std::invalid_argument("Invalid capacity");
        }

        edgesByVertex[fromVertex].emplace_back(std::make_shared<FlowEdge>(e));
        edgesByVertex[toVertex].emplace_back(edgesByVertex[fromVertex].back());
        ++numE;
    }

    [[nodiscard]]
    const std::vector<std::shared_ptr<FlowEdge>>& adj(int v) const override {
        if(!validVertex(v)) throw std::invalid_argument("Invalid vertex ID");
        return edgesByVertex[v];
    }

    [[nodiscard]]
    std::vector<std::shared_ptr<FlowEdge>> edges() const override {
        std::vector<std::shared_ptr<FlowEdge>> result;
        result.reserve(numE);
        for (size_t i=0; i<edgesByVertex.size(); ++i) {
            const auto& edgesVec = edgesByVertex[i];

            for(const auto& edge : edgesVec) {
                if (static_cast<int>(i) == edge->from()) {
                    // only add edges once
                    result.emplace_back(edge);
                }
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
    std::vector<std::vector<std::shared_ptr<FlowEdge>>> edgesByVertex {};

    [[nodiscard]]
    bool validVertex(int v) const {
        return v >= 0 && static_cast<size_t>(v) < edgesByVertex.size();
    }
};

#endif //WEIGHTED_GRAPHS_CPP_ADJACENCYLISTFLOWNETWORK_H
