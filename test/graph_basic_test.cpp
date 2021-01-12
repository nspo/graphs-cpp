#include "gtest/gtest.h"
#include <memory>
#include <fstream>
#include "Graph.h"

// graph source of tinyG.txt
const char* tinyG = R"(13
13
0 5
4 3
0 1
9 12
6 4
5 4
0 2
11 12
9 10
0 6
7 8
9 11
5 3
)";

// read graph from constant
std::unique_ptr<graph::Graph> readGraph() {
    std::istringstream iss(tinyG);
    std::unique_ptr<graph::Graph> pGraph = std::make_unique<graph::AdjacencyListGraph>(iss);
    return pGraph;
}

// not testing everything yet (WIP)

TEST(basic_test, basic_ops) { // NOLINT
    auto pGraph = readGraph();

    EXPECT_NO_THROW(pGraph->toString());
    EXPECT_EQ(degree(*pGraph, 0), 4);
    EXPECT_EQ(degree(*pGraph, 1), 1);
    EXPECT_ANY_THROW(degree(*pGraph, 20));
    EXPECT_EQ(graph::maxDegree(*pGraph), 4);
    EXPECT_EQ(graph::avgDegree(*pGraph), 2);
    EXPECT_EQ(graph::numSelfLoops(*pGraph), 0);
}

TEST(basic_test, dfs) { // NOLINT
    auto pGraph = readGraph();

    EXPECT_ANY_THROW(graph::find_paths_to_all::fromVertexToAllDfs(*pGraph, 30));
    const auto dfs_from_0 = graph::find_paths_to_all::fromVertexToAllDfs(*pGraph, 0);
    EXPECT_FALSE(dfs_from_0.hasPathTo(10));
    EXPECT_TRUE(dfs_from_0.hasPathTo(3));
    EXPECT_GE(dfs_from_0.pathTo(3).size(), 3);

    const auto dfs_from_0_noRec = graph::find_paths_to_all::fromVertexToAllDfsNoRec(*pGraph, 0);
    EXPECT_TRUE(dfs_from_0 == dfs_from_0_noRec);
    EXPECT_TRUE(dfs_from_0 == graph::find_paths_to_all::fromVertexToAllDfsNoRec(*pGraph, 0));
}

TEST(basic_test, bfs) { // NOLINT
    auto pGraph = readGraph();

    EXPECT_ANY_THROW(graph::find_paths_to_all::fromVertexToAllBfs(*pGraph, 30));
    const auto bfs_from_0 = graph::find_paths_to_all::fromVertexToAllBfs(*pGraph, 0);
    EXPECT_FALSE(bfs_from_0.hasPathTo(10));
    EXPECT_TRUE(bfs_from_0.hasPathTo(3));
    EXPECT_EQ(bfs_from_0.pathTo(3).size(), 3);

    const auto dfs_from_0 = graph::find_paths_to_all::fromVertexToAllDfs(*pGraph, 0);
    EXPECT_TRUE(bfs_from_0 != dfs_from_0);
}

TEST(basic_test, connectedComponents) { // NOLINT
    auto pGraph = readGraph();

    EXPECT_EQ(graph::ConnectedComponents(*pGraph).components().size(), 3);
}

TEST(basic_test, bipartiteness) { // NOLINT
    auto pGraph = readGraph();

    EXPECT_FALSE(graph::isBipartite(*pGraph));
}