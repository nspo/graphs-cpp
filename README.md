# Graphs with modern C++

## General
- Code for graph problems
- uses modern C++ instead of `new` and other dated patterns; e.g.
  - `std::vector`
  - `std::unique_ptr`
- unit tests under `test/`
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

## `include/Graph.h`
- Simple (undirected) `Graph` interface
- `AdjacencyListGraph` (https://en.wikipedia.org/wiki/Adjacency_list)
- Basic utility functions (a few)
- Find paths starting at a vortex to all connected vertices
  - with [Depth-first Search (DFS)](https://en.wikipedia.org/wiki/Depth-first_search) recursively (`graph::find_paths_to_all::fromVertexToAllDfs`)
  - with DFS iteratively (`graph::find_paths_to_all::fromVertexToAllDfsNoRec`)
  - with [Breadth-first Search (BFS)](https://en.wikipedia.org/wiki/Breadth-first_search) iteratively (`graph::find_paths_to_all::fromVertexToAllBfs`)
- Find connected components (https://en.wikipedia.org/wiki/Component_(graph_theory)) with DFS (`graph::ConnectedComponents`)
- Check whether a graph is [bipartite](https://en.wikipedia.org/wiki/Bipartite_graph) with DFS (`graph::isBipartite`)

## `main.cpp`
- Basic test of `Graph.h` functionality
- Reads graphs from standard input (`./graphs_test < tinyG.txt`) or file given as program argument (`./graphs_test tinyG.txt`) 
- Sample graph from `tinyG.txt`:
  ![](picTinyG.png)

## References
- Algorithms, [Part II](https://www.coursera.org/learn/algorithms-part2/home/welcome) by Princeton University (Robert Sedgewick, Kevin Wayne)