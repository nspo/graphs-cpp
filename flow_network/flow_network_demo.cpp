#include <iostream>
#include <fstream>
#include <memory>
#include "AdjacencyListFlowNetwork.h"
#include "FordFulkerson.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<FlowNetwork> fn;
    if(argc > 1) {
        std::cout<<"Reading flow network from file '"<<argv[1]<<"'...\n";
        std::ifstream ifs(argv[1]);
        if (!ifs) throw std::invalid_argument("Cannot open file");
        fn = std::make_unique<AdjacencyListFlowNetwork>(ifs);
    } else {
        std::cout<<"Reading flow network from standard input...\n";
        fn = std::make_unique<AdjacencyListFlowNetwork>(std::cin);
    }

    std::cout << *fn << "\n";
    std::cout<<"---\n";

    if (fn->V() > 1) {
        FordFulkerson ff(*fn, 0, fn->V()-1);
        std::cout<< "Max flow: "<<ff.getValue()<<"\n";
        std::cout<< "Source-side vertices in min cut (source="<<0<<", sink="<<fn->V()-1<<"): ";
        for (int i=0; i < fn->V(); ++i) {
            if (ff.isInCut(i)) {
                std::cout << i << " ";
            }
        }
        std::cout<<"\n";
    }

    return 0;
}
