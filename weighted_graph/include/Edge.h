#ifndef WEIGHTED_GRAPHS_CPP_EDGE_H
#define WEIGHTED_GRAPHS_CPP_EDGE_H

#include <ostream>
#include <unordered_set>

class Edge {
public:
    explicit Edge(int v, int w, double _weight) : vertex1{v}, vertex2{w}, weight{_weight}
    {}

    // return either vertex
    [[nodiscard]]
    int either() const {
        return vertex1;
    }

    // return the other endpoint that is not v
    [[nodiscard]]
    int other(int v) const {
        if (v==vertex1) {
            return vertex2;
        } else if (v==vertex2) {
            return vertex1;
        } else {
            throw std::invalid_argument("v is not a vertex of edge");
        }
    }

    [[nodiscard]]
    double getWeight() const {
        return weight;
    }

private:
    int vertex1;
    int vertex2;
    double weight;

};

// compare by weight
bool operator<(const Edge& lhs, const Edge& rhs) {
    return lhs.getWeight() < rhs.getWeight();
}
bool operator>(const Edge& lhs, const Edge& rhs) {
    return lhs.getWeight() > rhs.getWeight();
}

// create hash for Edge (for hash tables)
namespace std {
    template<>
    struct hash<Edge> {
        size_t operator()(const Edge& e) const {
            // make sure that order of vertices does not matter
            auto v1 = e.either();
            auto v2 = e.other(v1);
            auto vMin = std::min(v1, v2);
            auto vMax = e.other(vMin);

            size_t res = 17;
            res = 31*res + hash<decltype(vMin)>()(vMin);
            res = 31*res + hash<decltype(vMax)>()(vMax);
            res = 31*res + hash<decltype(e.getWeight())>()(e.getWeight());
            return res;
        }
    };
}

std::ostream& operator<<(std::ostream& os, const Edge& e) {
    int v1 = e.either();
    int v2 = e.other(v1);
    return os << "Edge (" << v1 << ")--"<<e.getWeight()<<"--("<<v2<<")";
}

#endif //WEIGHTED_GRAPHS_CPP_EDGE_H
