#ifndef GRAPHS_CPP_PRINTHELPERS_H
#define GRAPHS_CPP_PRINTHELPERS_H

#include <vector>
#include <string_view>

// print elements of a vector to stdout or ostream separated by delimiter and with last at the end
template<typename T>
void print_vec(const std::vector<T>& vec, std::string_view delimiter="->", std::string_view last="\n",
               std::ostream& os = std::cout) {
    if(vec.empty()) return;

    bool first=true;
    for(const auto& elem : vec) {
        if(first) {
            first = false;
        } else {
            os << delimiter;
        }
        os<<elem;
    }
    os<<last;
}

#endif //GRAPHS_CPP_PRINTHELPERS_H
