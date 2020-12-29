#include <iostream>
#include <fstream>
#include <memory>
#include "Graph.h"

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

    std::cout << pGraph->toString() << "\n";
    return 0;
}
