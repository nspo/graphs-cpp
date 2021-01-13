#ifndef WEIGHTED_GRAPHS_CPP_PRIORITYQUEUE_H
#define WEIGHTED_GRAPHS_CPP_PRIORITYQUEUE_H

#include <vector>

template<typename Key, typename CompareShouldGoDown>
class PriorityQueue {
public:
    // create empty priority queue
    PriorityQueue() : queue(1) {} // keep first element empty for simpler indices

    // insert a key into the priority queue
    void insert(Key key) {
        queue.emplace_back(std::move(key));
        swim(queue.size()-1);
    }

    // return first element in heap (minimum or maximum)
    [[nodiscard]]
    Key peekFirst() const {
        if(queue.size() < 2) throw std::out_of_range("Priority Queue is empty");
        return queue[1];
    }

    // delete and return first element in heap (minimum or maximum)
    Key deleteFirst() {
        if(queue.size() < 2) throw std::out_of_range("Priority Queue is empty");
        Key max = std::move(queue[1]);
        queue[1] = queue.back(); // no move here to avoid move to self in corner case
        queue.pop_back();
        sink(1); // sink will check if invalid
        return max;
    }

    [[nodiscard]]
    bool empty() const {
        return queue.size() == 1; // consider extra element
    }

private:
    std::vector<Key> queue;

    // swim key up as far as necessary
    void swim(size_t k) {
        while (k>1 && k < queue.size() && CompareShouldGoDown()(queue[k / 2], queue[k])) {
            std::swap(queue[k], queue[k/2]);
            k = k/2;
        }
    }

    // sink key down as far as necessary
    void sink(size_t k) {
        while(2*k < queue.size()) {
            // at least one child exists
            size_t childIdx = 2*k;
            if(childIdx+1 < queue.size() && CompareShouldGoDown()(queue[childIdx], queue[childIdx + 1])) {
                ++childIdx; // use second child
            }
            if(!CompareShouldGoDown()(queue[k], queue[childIdx])) {
                break;
            }
            std::swap(queue[k], queue[childIdx]);
            k = childIdx;
        }
    }

};

template<typename Key>
using MaxPriorityQueue = PriorityQueue<Key, std::less<Key>>;

template<typename Key>
using MinPriorityQueue = PriorityQueue<Key, std::greater<Key>>;

#endif //WEIGHTED_GRAPHS_CPP_PRIORITYQUEUE_H
