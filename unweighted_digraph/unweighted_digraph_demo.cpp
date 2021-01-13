#include <iostream>
#include <fstream>
#include "Digraph.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<digraph::Digraph> pGraph;
    if(argc > 1) {
        // try to read digraph from filename
        std::ifstream ifs(argv[1]);
        pGraph = std::make_unique<digraph::AdjacencyListDigraph>(ifs);

    } else {
        // try to read digraph from stdin
        pGraph = std::make_unique<digraph::AdjacencyListDigraph>(std::cin);
    }

    std::cout<<pGraph->toString()<<"\n";
    std::cout<<"---\n";

    const auto cycle = digraph::containsCycle(*pGraph);
    if(cycle) {
        std::cout<<"Cycle found: ";
        print_vec(*cycle);
    } else {
        std::cout<<"No cycle found\n";
        std::cout<<"Topological sort: ";
        const auto topologicalSort = digraph::topologicalSort(*pGraph);
        print_vec(topologicalSort);
    }
    std::cout<<"---\n";

    std::cout<<"Strongly connected components: \n";
    const auto comps = digraph::StronglyConnectedComponents(*pGraph).components();
    for(size_t i=0; i<comps.size(); ++i) {
        std::cout<<"Component "<<i<<": ";
        print_vec(comps[i], "-");
    }

    std::cout<<"---\n";

    return 0;
}
