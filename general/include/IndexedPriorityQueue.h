#ifndef WEIGHTED_GRAPHS_CPP_INDEXEDPRIORITYQUEUE_H
#define WEIGHTED_GRAPHS_CPP_INDEXEDPRIORITYQUEUE_H

#include <vector>
#include <optional>

template<typename Key, typename CompareShouldGoDown>
class IndexedPriorityQueue {
public:
    /// create empty priority queue
    /// @param maxSize Maximum number of elements in the PQ. Elements will have IDs between 0 and maxSize-1.
    explicit IndexedPriorityQueue(const size_t maxSize) :
            N(0), // no elements in priority queue at start
            keys(maxSize),
            pq(maxSize+1), // keep first PQ element empty
            qp(maxSize, std::nullopt) // init with std::nullopt to show elements are not in pq
    {}

    /// insert ID id with priority key into the priority queue
    void insert(const size_t id, const Key key) {
        if(N + 1 == pq.size()) throw std::invalid_argument("Priority Queue is full");
        if(id >= qp.size()) throw std::invalid_argument("ID too large");
        if(qp[id].has_value()) throw std::invalid_argument("ID is already in use");
        ++N;
        qp[id] = N;
        pq[N] = id;
        keys[id] = key;
        swim(N);
    }

    /// return ID of first element in heap (minimum or maximum)
    [[nodiscard]]
    size_t peekFirst() const {
        if(N == 0) throw std::out_of_range("Priority Queue is empty");
        return pq[1];
    }

    /// delete and return ID of first element in heap (minimum or maximum)
    size_t removeFirst() {
        if(N == 0) throw std::out_of_range("Priority Queue is empty");
        const size_t indexOfMin = pq[1];
        exchange(1, N--);
        sink(1);
        qp[pq[N+1]] = std::nullopt;
        return indexOfMin;
    }

    /// delete ID id
    void remove(const size_t id) {
        if(id >= qp.size()) throw std::invalid_argument("ID too large");
        if(!qp[id].has_value()) throw std::invalid_argument("ID is not in use");
        const size_t oldPosOfId = *qp[id];
        exchange(oldPosOfId, N--);
        swim(oldPosOfId);
        sink(oldPosOfId);
        qp[pq[N+1]] = std::nullopt;
    }

    /// change priority of element with ID id
    void changeKey(const size_t id, const Key newPriority) {
        if(id >= qp.size()) throw std::invalid_argument("ID too large");
        if(!qp[id].has_value()) throw std::invalid_argument("ID is not in use");
        keys[id] = newPriority;
        // fix order
        swim(*qp[id]);
        sink(*qp[id]);
    }

    /// whether priority queue is empty
    [[nodiscard]]
    bool empty() const {
        return N == 0;
    }

    /// whether the ID id is currently an element
    [[nodiscard]]
    bool contains(const size_t id) const {
        return id < qp.size() && qp[id].has_value();
    }

private:
    size_t N;
    std::vector<Key> keys; /// items with priorities, not in heap-order
    std::vector<size_t> pq; /// binary heap, with pq[1] being the index of the most prioritized item key in keys
    std::vector<std::optional<size_t>> qp; /// *qp[i] is position of ID id in pq, i.e. pq[*qp[id]] = id = *qp[pq[id]]

    /// whether key at index i in PQ must be lower in tree than key at index j (false if keys are equal)
    [[nodiscard]]
    bool lower(const size_t i, const size_t j) const {
        return CompareShouldGoDown()(keys[pq[i]], keys[pq[j]]);
    }

    /// swap values at PQ indices i and j
    void exchange(const size_t i, const size_t j) {
        std::swap(qp[pq[i]], qp[pq[j]]);
        std::swap(pq[i], pq[j]);
    }

    /// swim key in PQ up as far as necessary
    void swim(size_t k) {
        while (k>1 && lower(k / 2, k)) {
            exchange(k, k/2);
            k = k/2;
        }
    }

    /// sink key in PQ down as far as necessary
    void sink(size_t k) {
        while(2*k <= N) {
            // at least one child exists
            size_t childIdx = 2*k;
            if(childIdx < N && lower(childIdx, childIdx + 1)) {
                ++childIdx; // use second child
            }
            if(!lower(k, childIdx)) {
                break;
            }
            exchange(k, childIdx);
            k = childIdx;
        }
    }

};

template<typename Key>
using IndexedMaxPriorityQueue = IndexedPriorityQueue<Key, std::less<Key>>;

template<typename Key>
using IndexedMinPriorityQueue = IndexedPriorityQueue<Key, std::greater<Key>>;

#endif //WEIGHTED_GRAPHS_CPP_INDEXEDPRIORITYQUEUE_H
