#include <iostream>
#include <fstream>
#include <memory>
#include "Graph.h"

using namespace graph;

void print_vec(const std::vector<int>& vec, const char* delim="->", const char* last="\n") {
    if(vec.empty()) return;

    bool first=true;
    for(const auto& elem : vec) {
        if(first) {
            first = false;
        } else {
            std::cout<<delim;
        }
        std::cout<<elem;
    }
    std::cout<<last;
}

int main(int argc, char* argv[]) {
    std::unique_ptr<Graph> pGraph;
    if(argc > 1) {
        // try to read filename
        std::ifstream ifs(argv[1]);
        pGraph = std::make_unique<AdjacencyListGraph>(ifs);
    } else {
        // try to read stdin
        pGraph = std::make_unique<AdjacencyListGraph>(std::cin);
    }

    // basic ops
    std::cout << pGraph->toString() << "\n";
    std::cout << "Degree of v[1]: " << degree(*pGraph, 1) << "\n";
    std::cout << "Max degree: " << maxDegree(*pGraph) << "\n";
    std::cout << "Average degree: " << avgDegree(*pGraph) << "\n";
    std::cout << "Number of self-loops: " << numSelfLoops(*pGraph) << "\n";

    // Depth First Search
    PathsFromDFS pathsFrom0(*pGraph, 0);
    std::cout<<"All DFS paths from 0: \n";
    for(int i=0; i<pGraph->V(); ++i) {
        if(pathsFrom0.hasPathTo(i)) {
            std::cout<<"0 to "<<i<<": ";
            print_vec(pathsFrom0.pathTo(i));
        }
    }
    return 0;
}
