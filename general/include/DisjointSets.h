#ifndef WEIGHTED_GRAPHS_CPP_DISJOINTSETS_H
#define WEIGHTED_GRAPHS_CPP_DISJOINTSETS_H

#include <vector>

// Disjoint-sets data structure with path compression and union-by-rank
class DisjointSets {
public:
    // construct with elements 0 to numElements-1 all in disjoint sets
    explicit DisjointSets(int numElements) :
            parent(numElements, -1), rank(numElements, 0) {
        for(int i=0; i<numElements; ++i) {
            parent[i] = i;
        }
    }

    // connect p and q, or throw for invalid arguments
    void setUnion(const int p, const int q) {
        checkIndex(p); checkIndex(q);
        const int rp = findRoot(p);
        const int rq = findRoot(q);
        if (rp == rq) return;

        // union-by-rank
        if (rank[rp] > rank[rq]) {
            // rp has a higher upper bound on its height
            parent[rq] = rp;
        } else {
            // rq has higher or equal rank
            parent[rp] = rq;
            if (rank[rp] == rank[rq]) {
                // ranks were equal
                ++rank[rq];
            }
        }
    }

    // return whether p and q are in the same set, or throw for invalid arguments
    [[nodiscard]]
    bool connected(const int p, const int q) {
        checkIndex(p); checkIndex(q);
        return findRoot(p) == findRoot(q);
    }

    // return number of elements (the number of disjoint sets may be smaller)
    [[nodiscard]]
    int size() const {
        return parent.size();
    }

private:
    std::vector<int> parent; // parent of each element
    std::vector<int> rank; // upper bound on the number of edges until a leaf is reached

    // find the root of p
    [[nodiscard]]
    int findRoot(const int p) {
        if (p != parent[p]) {
            // Path compression: recursively search for root and attach p directly to it afterwards
            parent[p] = findRoot(parent[p]);
        }
        return parent[p];
    }

    // check index and throw if invalid
    void checkIndex(const int p) const {
        if(p < 0 || static_cast<size_t>(p) >= parent.size()) {
            throw std::invalid_argument("Invalid index passed in");
        }
    }
};

#endif //WEIGHTED_GRAPHS_CPP_DISJOINTSETS_H
