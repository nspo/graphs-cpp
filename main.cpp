#include <iostream>
#include <fstream>
#include <memory>
#include "Graph.h"

// print elements of a vector to stdout separated by delimiter and with last at the end
void print_vec(const std::vector<int>& vec, const char* delimiter="->", const char* last="\n") {
    if(vec.empty()) return;

    bool first=true;
    for(const auto& elem : vec) {
        if(first) {
            first = false;
        } else {
            std::cout << delimiter;
        }
        std::cout<<elem;
    }
    std::cout<<last;
}

// print all paths saved in paths to stdout
void print_paths(const graph::Graph& g, const graph::PathsFromVertexResult& paths) {
    for(int i=0; i<g.V(); ++i) {
        if(paths.hasPathTo(i)) {
            std::cout << "0 to " << i << " (dist=" << paths.distanceTo(i) << "): ";
            print_vec(paths.pathTo(i));
        }
    }
}

int main(int argc, char* argv[]) {
    std::unique_ptr<graph::Graph> pGraph;
    if(argc > 1) {
        // try to read file passed as argument
        std::ifstream ifs(argv[1]);
        pGraph = std::make_unique<graph::AdjacencyListGraph>(ifs);
    } else {
        // try to read stdin
        pGraph = std::make_unique<graph::AdjacencyListGraph>(std::cin);
    }

    // basic ops
    std::cout << pGraph->toString() << "\n";
    std::cout << "Degree of v[1]: " << degree(*pGraph, 1) << "\n";
    std::cout << "Max degree: " << maxDegree(*pGraph) << "\n";
    std::cout << "Average degree: " << avgDegree(*pGraph) << "\n";
    std::cout << "Number of self-loops: " << numSelfLoops(*pGraph) << "\n";
    std::cout<<"----\n";

    // Depth-first Search
    graph::PathsFromVertexResult dfs_from_0 = graph::depth_first_search::fromVertexToAll(*pGraph, 0);
    std::cout<<"Found DFS paths from 0: \n";
    print_paths(*pGraph, dfs_from_0);
    std::cout<<"----\n";

    // Breadth-first Search
    graph::PathsFromVertexResult bfs_from_0 = graph::breadth_first_search::fromVertexToAll(*pGraph, 0);
    std::cout<<"Found BFS paths from 0: \n";
    print_paths(*pGraph, bfs_from_0);
    std::cout<<"----\n";

    // Connected components
    graph::ConnectedComponents connectedComponents(*pGraph);
    std::cout<<"Number of connected components: "<<connectedComponents.count()<<"\n";
    std::cout<<"All connected components in graph: \n";
    for(const auto& comp : connectedComponents.components()) {
        print_vec(comp, " ");
    }
    std::cout<<"----\n";


    return 0;
}
