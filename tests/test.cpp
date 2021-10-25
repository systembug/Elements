//
// Created by systembug on 21. 9. 19..
//

#include "gtest/gtest.h"
#include "../src/basics/Vec.hpp"

namespace elements::tests {
    TEST(Vec, static_same_test) {
        elements::basics::Vec<float, 10> vec1, vec2;
        EXPECT_EQ(vec1 == vec2, true);
        EXPECT_EQ(vec2 == vec1, true);
        vec1[5] = 3;
        EXPECT_EQ(vec1 == vec2, false);
    }

    TEST(Vec, dynamic_same_test) {
        elements::basics::Vec<float> vec1(10, 0);
        elements::basics::Vec<float> vec2(10, 0);
        EXPECT_EQ(vec1 == vec2, true);
        EXPECT_EQ(vec2 == vec1, true);
        vec2[8] = -2.3;
        EXPECT_EQ(vec1 == vec2, false);
    }

    TEST(Vec, fusion_same_test) {
        elements::basics::Vec<float, 10> vec1;
        elements::basics::Vec<float> vec2(10, 0);
        EXPECT_EQ(vec1 == vec2, true);
        EXPECT_EQ(vec2 == vec1, true);
        vec2.at(3) = 1;
        EXPECT_EQ(vec1 == vec2, false);
    }

    TEST(Vec, static_comparison_test) {
        elements::basics::Vec<float, 2> vec1, vec2;
        vec1.at(0) = 1;
        vec1.at(1) = 2;
        vec2.at(0) = 0;
        vec2.at(1) = 0;
        EXPECT_EQ(vec1 > vec2, true);
        EXPECT_EQ(vec1 < vec2, false);
        EXPECT_EQ(vec1 >= vec2, true);
        EXPECT_EQ(vec1 <= vec2, false);
    }

    TEST(Vec, dynamic_comparison_test) {
        elements::basics::Vec<float> vec1(2, 0);
        elements::basics::Vec<float> vec2(2, 0);
        vec1.at(0) = 1;
        vec1.at(1) = 2;
        EXPECT_EQ(vec1 > vec2, true);
        EXPECT_EQ(vec1 < vec2, false);
        EXPECT_EQ(vec1 >= vec2, true);
        EXPECT_EQ(vec1 <= vec2, false);
    }

    TEST(Vec, fusion_comparison_test) {
        elements::basics::Vec<float, 2> vec1;
        elements::basics::Vec<float> vec2(2, 0);
        vec1.at(0) = 0;
        vec1.at(1) = 0;
        vec2.at(0) = 1;
        vec2.at(1) = 2;
        EXPECT_EQ(vec1 > vec2, false);
        EXPECT_EQ(vec1 < vec2, true);
        EXPECT_EQ(vec1 >= vec2, false);
        EXPECT_EQ(vec1 <= vec2, true);
    }

    TEST(Vec, static_copy_test) {
        elements::basics::Vec<float, 5> vec1, vec2;
        vec2[4] = 3;
        vec1 = vec2;
        EXPECT_EQ(vec1 == vec2, true);
        vec1[0] = -0.33;
        auto vec3(vec1);
        EXPECT_EQ(vec1 == vec3, true);
    }

    TEST(Vec, dynamic_copy_test) {
        elements::basics::Vec<float> vec1(10, 2);
        auto vec2 = vec1;
        EXPECT_EQ(vec1 == vec2, true);
        vec1[0] = -0.33;
        auto vec3(vec1);
        EXPECT_EQ(vec1 == vec3, true);
    }

    TEST(Vec, static_move_test) {
        elements::basics::Vec<int32_t> vec1 = {1, 2, 3, 4, 5};
        elements::basics::Vec<int32_t, 5> vec2 = {1, 2, 3, 4, 5};
        auto vec3 = std::move(vec2);

        // int32_t has same operation with copy and move.
        EXPECT_EQ(vec2 == vec3, false);
        EXPECT_EQ(vec1 == vec3, true);
    }

    TEST(Vec, dynamic_move_test) {
        elements::basics::Vec<int32_t> vec1 = {1, 2, 3, 4, 5};
        elements::basics::Vec<int32_t, 5> vec2 = {1, 2, 3, 4, 5};
        auto vec3 = std::move(vec1);
        EXPECT_EQ(vec2 == vec3, true);
        EXPECT_EQ(vec1 == vec3, false);
    }

    TEST(Vec, size_test) {
        elements::basics::Vec<int32_t, 100> vec1;
        elements::basics::Vec<int32_t> vec2(10, 49);
        EXPECT_EQ(vec1.size() == 100, true);
        EXPECT_EQ(vec2.size() == 10, true);
    }

    TEST(Vec, addition_test) {
        elements::basics::Vec<int32_t, 4> vec1 = {1, 2, 3, 4};
        elements::basics::Vec<int32_t, 4> vec2 = {4, 3, 2, 1};
        elements::basics::Vec<int32_t, 4> vec3 = {5, 5, 5, 5};
        auto sum = vec1 + vec2;
        EXPECT_EQ(sum == vec3, true);
    }
}