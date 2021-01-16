#include <iostream>
#include <fstream>
#include <memory>
#include <SingleSourceAcyclicShortestPath.h>
#include <SingleSourceBellmanFordShortestPath.h>
#include "EdgeWeightedAdjacencyListDigraph.h"
#include "SingleSourceDijkstraShortestPath.h"
#include "TopologicalSort.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<EdgeWeightedDigraph> digraph;
    if(argc > 1) {
        std::cout<<"Reading digraph from file '"<<argv[1]<<"'...\n";
        std::ifstream ifs(argv[1]);
        if (!ifs) throw std::invalid_argument("Cannot open file");
        digraph = std::make_unique<EdgeWeightedAdjacencyListDigraph>(ifs);
    } else {
        std::cout<<"Reading digraph from standard input...\n";
        digraph = std::make_unique<EdgeWeightedAdjacencyListDigraph>(std::cin);
    }

    std::cout << *digraph << "\n";
    std::cout<<"---\n";

    const int from = 0;

    std::unique_ptr<SingleSourceShortestPath> sssp;
    if (auto cycle = containsCycle(*digraph); cycle) {
        std::cout<<"Digraph contains at least one cycle: ";
        print_vec(*cycle);

        bool containsNegativeEdgeWeight = false;
        for(int v=0; v<digraph->V(); ++v) {
            for(const auto& edge : digraph->adj(v)) {
                if (edge.weight() < 0) {
                    containsNegativeEdgeWeight = true;
                    break;
                }
            }
        }

        if (containsNegativeEdgeWeight) {
            std::cout<<"Digraph contains negative edge weights -> using Bellman-Ford algorithm for shortest paths\n";
            sssp = std::make_unique<SingleSourceBellmanFordShortestPath>(*digraph, from);
        } else {
            std::cout<<"Digraph does not contain negative edge weights -> using Dijkstra's algorithm for shortest paths\n";
            sssp = std::make_unique<SingleSourceDijkstraShortestPath>(*digraph, from);
        }

    } else {
        std::cout<<"Digraph does not contain a cycle (i.e. it's a DAG) -> using DAG algorithm for shortest paths\n";
        std::cout<<"Topological order: ";
        print_vec(topologicalSort(*digraph));

        sssp = std::make_unique<SingleSourceAcyclicShortestPath>(*digraph, from);
    }

    std::cout<<"Shortest paths from 0: \n";
    for(int to=0; to<digraph->V(); ++to) {
        // print path to to
        std::cout << from << " to " << to << " (" << sssp->distTo(to) << "): ";
        if (sssp->hasPathTo(to)) {
            for (const auto& edge : sssp->pathTo(to)) {
                std::cout<<edge<<" ";
            }
        } else {
            std::cout<<"No path found";
        }

        std::cout<<"\n";
    }

    std::cout<<"---\n";


    return 0;
}
