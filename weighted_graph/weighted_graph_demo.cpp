#include <iostream>
#include <fstream>
#include <memory>
#include "EdgeWeightedAdjacencyListGraph.h"
#include "MinimumSpanningTree.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<EdgeWeightedGraph> graph;
    if(argc > 1) {
        std::cout<<"Reading graph from file '"<<argv[1]<<"'...\n";
        std::ifstream ifs(argv[1]);
        if (!ifs) throw std::invalid_argument("Cannot open file");
        graph = std::make_unique<EdgeWeightedAdjacencyListGraph>(ifs);
    } else {
        std::cout<<"Reading graph from standard input...\n";
        graph = std::make_unique<EdgeWeightedAdjacencyListGraph>(std::cin);
    }

    std::cout<<*graph<<"\n";

    std::cout<<"---\n";
    std::cout<<"Minimum Spanning Tree:\n";
    MinimumSpanningTree mst{*graph};
    for (const auto& edge : mst.edges()) {
        std::cout<<edge<<"\n";
    }
    std::cout<<"Weight: "<<mst.weight()<<"\n";


    std::cout<<"";

    return 0;
}
