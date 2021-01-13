#ifndef WEIGHTED_GRAPHS_CPP_SINGLESOUREDIJKSTRASHORTESTPATH_H
#define WEIGHTED_GRAPHS_CPP_SINGLESOUREDIJKSTRASHORTESTPATH_H

#include "IndexedPriorityQueue.h"
#include "SingleSourceShortestPath.h"

class SingleSourceDijkstraShortestPath : public SingleSourceShortestPath {
public:
    SingleSourceDijkstraShortestPath(const EdgeWeightedDigraph &digraph, const int from) :
            SingleSourceShortestPath(digraph) {

        // Dijkstra's algorithm (assumes non-negative edge weights)
        distancesTo[from] = 0;

        IndexedMinPriorityQueue<double> pq(digraph.V()); // PQ for next vertex to visit
        pq.insert(from, 0.0);
        while(!pq.empty()) {
            const int v = pq.removeFirst();
            for(const auto& edge : digraph.adj(v)) {
                relax(edge, pq);
            }
        }
    }

private:
    // make use of edge if it gives the shortest path so far to e.to()
    void relax(const DirectedEdge& e, IndexedMinPriorityQueue<double>& pq) {
        const int from = e.from();
        const int to = e.to();
        if (distancesTo[to] > distancesTo[from] + e.weight()) {
            // use edge
            distancesTo[to] = distancesTo[from] + e.weight();
            edgesTo[to] = e;
            if (pq.contains(to)) {
                pq.changeKey(to, distancesTo[to]);
            } else {
                pq.insert(to, distancesTo[to]);
            }
        }
    }
};

#endif //WEIGHTED_GRAPHS_CPP_SINGLESOUREDIJKSTRASHORTESTPATH_H
