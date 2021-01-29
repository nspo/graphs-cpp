#include "IndexedPriorityQueue.h"
#include "FlowEdge.h"
#include "gtest/gtest.h"

TEST(flow_edge, basic) { // NOLINT
    FlowEdge e(1, 2, 10);
    EXPECT_EQ(e.from(), 1);
    EXPECT_EQ(e.to(), 2);
    EXPECT_EQ(e.other(1), 2);
    EXPECT_EQ(e.other(2), 1);
    EXPECT_ANY_THROW((void) e.other(3));
    EXPECT_EQ(e.flow(), 0);
    EXPECT_EQ(e.capacity(), 10);
    EXPECT_EQ(e.residualCapacityTo(1), 0);
    EXPECT_EQ(e.residualCapacityTo(2), 10);

    EXPECT_ANY_THROW(e.addResidualFlowTo(3, 5.0));
    EXPECT_ANY_THROW(e.addResidualFlowTo(2, 11.0));
    e.addResidualFlowTo(2, 5.0);
    EXPECT_EQ(e.flow(), 5);
    EXPECT_EQ(e.residualCapacityTo(1), 5);
    EXPECT_EQ(e.residualCapacityTo(2), 5);
    e.addResidualFlowTo(2, 5.0);
    EXPECT_EQ(e.flow(), 10);
    EXPECT_EQ(e.residualCapacityTo(1), 10);
    EXPECT_EQ(e.residualCapacityTo(2), 0);
    e.addResidualFlowTo(1, 10.0);
    EXPECT_EQ(e.residualCapacityTo(1), 0);
    EXPECT_EQ(e.residualCapacityTo(2), 10);
}


