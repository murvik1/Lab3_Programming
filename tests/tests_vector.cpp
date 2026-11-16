#include <gtest/gtest.h>
#include <algorithm>
#include <string>
#include "Vector_T.h"



TEST(VectorTest, NewVectorIsEmpty) {
    Vector<int> v;
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, PushBackIncreasesSize) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.size(), 2u);
}

TEST(VectorTest, AtThrowsOnBadIndex) {
    Vector<int> v;
    v.push_back(1);
    EXPECT_THROW(v.at(5), std::out_of_range);
}
