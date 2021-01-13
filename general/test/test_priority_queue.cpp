#include "IndexedPriorityQueue.h"
#include "PriorityQueue.h"
#include "gtest/gtest.h"

TEST(priority_queue, max_basic) { // NOLINT
    MaxPriorityQueue<int> pq;
    pq.insert(3);
    pq.insert(10);
    pq.insert(7);
    pq.insert(1);

    EXPECT_EQ(pq.deleteFirst(), 10);
    EXPECT_EQ(pq.deleteFirst(), 7);
    EXPECT_EQ(pq.deleteFirst(), 3);
    EXPECT_EQ(pq.deleteFirst(), 1);
}


TEST(priority_queue, min_basic) { // NOLINT
    MinPriorityQueue<int> pq;
    pq.insert(3);
    pq.insert(10);
    pq.insert(7);
    pq.insert(1);

    EXPECT_EQ(pq.peekFirst(), 1);
    EXPECT_EQ(pq.deleteFirst(), 1);
    EXPECT_EQ(pq.deleteFirst(), 3);
    EXPECT_EQ(pq.deleteFirst(), 7);
    EXPECT_EQ(pq.deleteFirst(), 10);
    EXPECT_TRUE(pq.empty());
    EXPECT_ANY_THROW(pq.deleteFirst());
}

TEST(priority_queue, max_indexed) { // NOLINT
    IndexedMaxPriorityQueue<int> pq(11);
    pq.insert(3, 3);
    pq.insert(10, 10);
    pq.insert(7, 7);
    pq.insert(1, 1);

    EXPECT_EQ(pq.removeFirst(), 10);
    EXPECT_EQ(pq.removeFirst(), 7);
    EXPECT_TRUE(pq.contains(3) && pq.contains(1));
    EXPECT_FALSE(pq.contains(10) || pq.contains(7));
    EXPECT_EQ(pq.removeFirst(), 3);
    EXPECT_EQ(pq.removeFirst(), 1);
    EXPECT_TRUE(pq.empty());

    pq.insert(1, 1);
    pq.insert(2, 2);
    pq.insert(3, 3);
    pq.insert(4, 4);
    EXPECT_EQ(pq.peekFirst(), 4);
    pq.changeKey(4, -1);
    EXPECT_EQ(pq.peekFirst(), 3);
    pq.changeKey(3, -2);
    EXPECT_EQ(pq.peekFirst(), 2);
    pq.changeKey(2, -3);
    EXPECT_EQ(pq.peekFirst(), 1);
    pq.changeKey(1, -4);
    EXPECT_EQ(pq.peekFirst(), 4);
    pq.changeKey(1, 20);
    pq.changeKey(2, 30);
    EXPECT_EQ(pq.removeFirst(), 2);
    EXPECT_EQ(pq.removeFirst(), 1);
    EXPECT_EQ(pq.removeFirst(), 4);
    EXPECT_EQ(pq.removeFirst(), 3);
    EXPECT_ANY_THROW(pq.removeFirst());
    EXPECT_ANY_THROW(pq.changeKey(1, 100));

    pq.insert(1, 1);
    pq.insert(2, 2);
    pq.insert(3, 3);
    pq.insert(4, 4);
    pq.remove(3);
    pq.remove(1);
    EXPECT_EQ(pq.removeFirst(), 4);
    EXPECT_EQ(pq.removeFirst(), 2);
    EXPECT_TRUE(pq.empty());
}

TEST(priority_queue, min_indexed_double) { // NOLINT
    IndexedMinPriorityQueue<double> pq(20);
    pq.insert(0, -1000);
    pq.insert(1, 1.2);
    pq.insert(2, 2.3);
    pq.insert(3, 3.4);
    pq.insert(4, 4.5);
    pq.insert(5, 5.6);
    EXPECT_ANY_THROW(pq.insert(20, std::numeric_limits<double>::infinity()));
    pq.insert(19, std::numeric_limits<double>::infinity());
    pq.changeKey(1, 7.2);
    pq.remove(3);
    EXPECT_EQ(pq.removeFirst(), 0);
    EXPECT_EQ(pq.removeFirst(), 2);
    EXPECT_EQ(pq.removeFirst(), 4);
    EXPECT_EQ(pq.removeFirst(), 5);
    EXPECT_EQ(pq.removeFirst(), 1);
    EXPECT_EQ(pq.removeFirst(), 19);
    EXPECT_TRUE(pq.empty());

    for(size_t i=0; i<20; ++i) {
        pq.insert(i, i*2.0);
    }
    EXPECT_ANY_THROW(pq.insert(10, 2.0));
    for(size_t i=0; i<20; ++i) {
        EXPECT_EQ(pq.removeFirst(), i);
    }
    EXPECT_TRUE(pq.empty());
}