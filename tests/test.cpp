//
// Created by systembug on 21. 9. 19..
//

#include "gtest/gtest.h"
#include "../src/basics/Vec.hpp"
#include <chrono>

HWY_BEFORE_NAMESPACE();
namespace elements::basics {
namespace HWY_NAMESPACE {
    TEST(Vec, static_same_test) {
        Vec<float, 10> vec1, vec2;
        EXPECT_EQ(vec1 == vec2, true);
        EXPECT_EQ(vec2 == vec1, true);
        vec1[5] = 3;
        EXPECT_EQ(vec1 == vec2, false);
    }

    TEST(Vec, dynamic_same_test) {
        Vec<float> vec1(10, 1);
        Vec<float> vec2(10, 1);
        EXPECT_EQ(vec1 == vec2, true);
        EXPECT_EQ(vec2 == vec1, true);
        vec2[8] = -2.3;
        EXPECT_EQ(vec1 == vec2, false);
    }

    TEST(Vec, fusion_same_test) {
        Vec<float, 10> vec1;
        Vec<float> vec2(10, 0);
        EXPECT_EQ(vec1 == vec2, true);
        EXPECT_EQ(vec2 == vec1, true);
        vec2.at(3) = 1;
        EXPECT_EQ(vec1 == vec2, false);
    }

    TEST(Vec, static_comparison_test) {
        Vec<float, 2> vec1, vec2;
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
        Vec<float> vec1(2, 0);
        Vec<float> vec2(2, 0);
        vec1.at(0) = 1;
        vec1.at(1) = 2;
        EXPECT_EQ(vec1 > vec2, false);
        EXPECT_EQ(vec1 < vec2, true);
        EXPECT_EQ(vec1 >= vec2, false);
        EXPECT_EQ(vec1 <= vec2, true);
    }

    TEST(Vec, fusion_comparison_test) {
        Vec<float, 2> vec1;
        Vec<float> vec2(2, 0);
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
        Vec<float, 5> vec1, vec2;
        vec2[4] = 3;
        vec1 = vec2;
        EXPECT_EQ(vec1 == vec2, true);
        vec1[0] = -0.33;
        auto vec3(vec1);
        EXPECT_EQ(vec1 == vec3, true);
    }

    TEST(Vec, dynamic_copy_test) {
        Vec<float> vec1(10, 2);
        auto vec2 = vec1;
        EXPECT_EQ(vec1 == vec2, true);
        vec1[0] = -0.33;
        auto vec3(vec1);
        EXPECT_EQ(vec1 == vec3, true);
    }

    TEST(Vec, static_move_test) {
        Vec<int32_t> vec1 = {1, 2, 3, 4, 5};
        Vec<int32_t, 5> vec2 = {1, 2, 3, 4, 5};
        auto vec3 = std::move(vec2);

        // int32_t has same operation with copy and move.
        EXPECT_EQ(vec2 == vec3, false);
        EXPECT_EQ(vec1 == vec3, true);
    }

    TEST(Vec, dynamic_move_test) {
        Vec<int32_t> vec1 = {1, 2, 3, 4, 5};
        Vec<int32_t, 5> vec2 = {1, 2, 3, 4, 5};
        auto vec3 = std::move(vec1);
        EXPECT_EQ(vec2 == vec3, true);
        EXPECT_EQ(vec1 == vec3, false);
    }

    TEST(Vec, size_test) {
        Vec<int32_t, 100> vec1;
        Vec<int32_t> vec2(10, 49);
        EXPECT_EQ(vec1.size() == 100, true);
        EXPECT_EQ(vec2.size() == 10, true);
    }

    TEST(Vec, static_addition_test) {
        Vec<int8_t, 255> vec1;
        Vec<int8_t, 255> vec2;
        Vec<int8_t, 255> vec3;

        std::fill(std::begin(vec1), std::end(vec1), 1);
        std::fill(std::begin(vec2), std::end(vec2), 2);
        std::fill(std::begin(vec3), std::end(vec3), 3);

        // auto prev = std::chrono::steady_clock::now();
        auto sum = vec1 + vec2;
        // auto duration = std::chrono::steady_clock::now() - prev;
        // std::cout << duration.count() << '\n';
        EXPECT_EQ(sum == vec3, true);
    }

    TEST(Vec, dynamic_addition_test) {
        Vec<float> vec1(64, 0.5);
        Vec<float> vec2(64, 0.2);
        Vec<float> vec3(64, 0.7);

        // auto prev = std::chrono::steady_clock::now();
        auto sum = vec1 + vec2;
        // auto duration = std::chrono::steady_clock::now() - prev;
        // std::cout << duration.count() << '\n';
        EXPECT_EQ(sum == vec3, true);
    }

    TEST(Vec, fusion_addition_test) {
        Vec<double> vec1(4096, 0.5);
        Vec<double, 4096> vec2;
        Vec<double, 4096> vec3;

        std::fill(std::begin(vec2), std::end(vec2), 0.2);
        std::fill(std::begin(vec3), std::end(vec3), 0.7);

        // auto prev = std::chrono::steady_clock::now();
        auto sum = vec1 + vec2;
        // auto duration = std::chrono::steady_clock::now() - prev;
        // std::cout << duration.count() << '\n';
        EXPECT_EQ(sum == vec3, true);
    }

    TEST(Vec, static_subtraction_test) {
        Vec<int8_t, 33> vec1;
        Vec<int8_t, 33> vec2;
        Vec<int8_t, 33> vec3;

        std::fill(std::begin(vec1), std::end(vec1), 3);
        std::fill(std::begin(vec2), std::end(vec2), 1);
        std::fill(std::begin(vec3), std::end(vec3), 2);

        // auto prev = std::chrono::steady_clock::now();
        auto sum = vec1 - vec2;
        // auto duration = std::chrono::steady_clock::now() - prev;
        // std::cout << duration.count() << '\n';
        EXPECT_EQ(sum == vec3, true);
    }

    TEST(Vec, dynamic_subtraction_test) {
        Vec<float> vec1(65536, 0.2);
        Vec<float> vec2(65536, 0.5);
        Vec<float> vec3(65536, -0.3);

        // auto prev = std::chrono::steady_clock::now();
        auto sum = vec1 - vec2;
        // auto duration = std::chrono::steady_clock::now() - prev;
        // std::cout << duration.count() << '\n';
        EXPECT_EQ(sum == vec3, true);
    }

    TEST(Vec, fusion_subtraction_test) {
        Vec<double> vec1(3452, 0.5);
        Vec<double, 3452> vec2;
        Vec<double, 3452> vec3;

        std::fill(std::begin(vec2), std::end(vec2), 0.2);
        std::fill(std::begin(vec3), std::end(vec3), 0.3);

        // auto prev = std::chrono::steady_clock::now();
        auto sum = vec1 - vec2;
        // auto duration = std::chrono::steady_clock::now() - prev;
        // std::cout << duration.count() << '\n';
        EXPECT_EQ(sum == vec3, true);
    }
}
}

HWY_AFTER_NAMESPACE();