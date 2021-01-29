#ifndef WEIGHTED_GRAPHS_CPP_FLOWEDGE_H
#define WEIGHTED_GRAPHS_CPP_FLOWEDGE_H

#include <ostream>
#include <unordered_set>

class FlowEdge {
public:
    explicit FlowEdge(int _from, int _to, double _capacity) :
            vertexFrom{_from}, vertexTo{_to}, edgeCapacity{_capacity}
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

    // return other vertex
    [[nodiscard]]
    int other(const int v) const {
        if (v == vertexFrom) {
            return vertexTo;
        } else if (v == vertexTo) {
            return vertexFrom;
        } else {
            throw std::invalid_argument("Invalid vertex");
        }
    }

    [[nodiscard]]
    double capacity() const {
        return edgeCapacity;
    }

    [[nodiscard]]
    double flow() const {
        return edgeFlow;
    }

    [[nodiscard]]
    double residualCapacityTo(const int v) const {
        if (v == vertexTo) {
            return edgeCapacity - edgeFlow;
        }
        else if (v == vertexFrom) {
            return edgeFlow;
        } else {
            throw std::invalid_argument("Invalid vertex");
        }
    }

    void addResidualFlowTo(const int v, const double delta) {
        if (delta > residualCapacityTo(v)) {
            throw std::invalid_argument("Delta too high");
        }

        if (v == vertexTo) {
            // forward
            edgeFlow += delta;
        } else { // validity already checked above
            // backward
            edgeFlow -= delta;
        }
    }

private:
    int vertexFrom;
    int vertexTo;
    double edgeCapacity;
    double edgeFlow = 0;
};

inline std::ostream& operator<<(std::ostream& os, const FlowEdge& e) {
    return os << e.from() << "->"<< e.to()<<" "<< e.flow() << "/" << e.capacity();
}

#endif //WEIGHTED_GRAPHS_CPP_FLOWEDGE_H
