#ifndef WEIGHTED_GRAPHS_CPP_DIRECTEDEDGE_H
#define WEIGHTED_GRAPHS_CPP_DIRECTEDEDGE_H

#include <ostream>
#include <unordered_set>

class DirectedEdge {
public:
    explicit DirectedEdge(int _from, int _to, double _weight) :
            vertexFrom{_from}, vertexTo{_to}, edgeWeight{_weight}
    {}

    // return start vertex
    [[nodiscard]]
    int from() const {
        return vertexFrom;
    }

    // return end vertex
    [[nodiscard]]
    int to() const {
        return vertexTo;
    }

    [[nodiscard]]
    double weight() const {
        return edgeWeight;
    }

private:
    int vertexFrom;
    int vertexTo;
    double edgeWeight;
};

// compare by weight
bool operator<(const DirectedEdge& lhs, const DirectedEdge& rhs) {
    return lhs.weight() < rhs.weight();
}
bool operator>(const DirectedEdge& lhs, const DirectedEdge& rhs) {
    return lhs.weight() > rhs.weight();
}

std::ostream& operator<<(std::ostream& os, const DirectedEdge& e) {
    return os << e.from() << "->"<< e.to()<<" "<<e.weight();
}

#endif //WEIGHTED_GRAPHS_CPP_DIRECTEDEDGE_H
