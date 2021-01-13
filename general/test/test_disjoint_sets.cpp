#include <random>
#include "gtest/gtest.h"
#include "DisjointSets.h"

TEST(disjoint_sets, basic) { // NOLINT
    DisjointSets disjointSets(20);

    disjointSets.setUnion(0, 1);
    EXPECT_TRUE(!disjointSets.connected(1, 2));
    disjointSets.setUnion(2, 3);
    EXPECT_TRUE(!disjointSets.connected(0, 2));
    disjointSets.setUnion(3, 4);
    EXPECT_TRUE(disjointSets.connected(2, 4));
    disjointSets.setUnion(5, 6);
    EXPECT_TRUE(disjointSets.connected(5, 6));

    // connect all remaining elements to each other
    for(int i=7; i+1 < disjointSets.size(); ++i) {
        disjointSets.setUnion(i, i + 1);
    }
    EXPECT_TRUE(disjointSets.connected(7, 19));
    EXPECT_TRUE(!disjointSets.connected(6, 19));
}

TEST(disjoint_sets, large) { // NOLINT
    DisjointSets sets(2000000);
    for(int i=0; i+2 < sets.size(); i += 2) {
        // connect every even element
        sets.setUnion(i, i+2);
    }
    EXPECT_TRUE(sets.connected(0, sets.size()-2));
    EXPECT_TRUE(!sets.connected(0, sets.size()-1));

    for(int i=1; i+2 < sets.size(); i += 2) {
        // connect every odd element
        sets.setUnion(i, i+2);
    }

    EXPECT_TRUE(sets.connected(1, sets.size()-1));
    EXPECT_TRUE(!sets.connected(0, sets.size()-1));

    sets.setUnion(0, 1); // should connect the two remaining disjoint sets
    EXPECT_TRUE(sets.connected(0, sets.size()-1));
    EXPECT_TRUE(sets.connected(0, sets.size()-2));
    EXPECT_TRUE(sets.connected(0, sets.size()-3));
}