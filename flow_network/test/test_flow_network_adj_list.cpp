#include "IndexedPriorityQueue.h"
#include "AdjacencyListFlowNetwork.h"
#include "gtest/gtest.h"

TEST(flow_network, basic) { // NOLINT
    AdjacencyListFlowNetwork fn(5);
    EXPECT_EQ(fn.V(), 5);
    EXPECT_EQ(fn.E(), 0);
    EXPECT_EQ(fn.edges().size(), 0);

    fn.addEdge(FlowEdge(0, 1, 5));
    fn.addEdge(FlowEdge(1, 2, 5));
    fn.addEdge(FlowEdge(2, 3, 5));
    fn.addEdge(FlowEdge(3, 4, 20));
    EXPECT_EQ(fn.E(), 4);
    EXPECT_EQ(fn.edges().size(), 4);

    EXPECT_EQ(fn.adj(0)[0]->to(), 1);
    EXPECT_EQ(fn.adj(0)[0]->flow(), 0);
    EXPECT_EQ(fn.adj(1)[0]->from(), 0);
    EXPECT_EQ(fn.adj(1)[1]->from(), 1);
    EXPECT_EQ(fn.adj(0)[0]->residualCapacityTo(1), 5);
    EXPECT_EQ(fn.adj(1)[0]->residualCapacityTo(0), 0);
    EXPECT_EQ(fn.adj(4)[0]->residualCapacityTo(4), 20);

    std::cout << fn<<"\n";
}


