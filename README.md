# Graphs with modern C++

## General
- Code for graph problems
- uses modern C++ instead of `new` and other dated patterns; e.g.
  - `std::vector`
  - `std::unique_ptr`
- this is an example project and not a huge library

## Compilation
- Manually: `g++ -std=c++17 -O3 main.cpp -o graphs_test`
- or with `cmake`:
  ```bash
  mkdir build
  cd build/
  cmake ..
  make
  ```

## `Graph.h`
- Simple `Graph` interface
- `AdjacencyListGraph` (https://en.wikipedia.org/wiki/Adjacency_list)
- Utility functions (a few)
- Depth-first Search (DFS, https://en.wikipedia.org/wiki/Depth-first_search)
- Breadth-first Search (BFS, https://en.wikipedia.org/wiki/Breadth-first_search)

## `main.cpp`
- Basic test of `Graph.h` functionality
- Reads graphs from standard input (`./graphs_test < tinyG.txt`) or file given as program argument (`./graphs_test tinyG.txt`) 
  ![](picTinyG.png)

## References
- Algorithms, [Part II](https://www.coursera.org/learn/algorithms-part2/home/welcome) by Princeton University (Robert Sedgewick, Kevin Wayne)