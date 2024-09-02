#include <fmt/core.h>
#include <gtest/gtest.h>

#include <cstddef> // std::size_t
#include <vector>

TEST(TestSuite, BasicAssertions) {
    EXPECT_STRNE("hello\n", fmt::format("{}\n", 42).c_str());
    EXPECT_EQ(7 * 6, 42);
}

class TestFixture : public testing::Test {
  protected:
    void SetUp() override {
        // Setup for test
        v1 = {1, 2, 3};
        v2 = {1.0, 2.0, 3.0};
    }

    std::vector<int> v1;
    std::vector<float> v2;
};

TEST_F(TestFixture, VectorSize) {
    ASSERT_TRUE(!v1.empty());
    EXPECT_EQ(v1.size(), v2.size());
}

TEST_F(TestFixture, VectorElement) {
    for (std::size_t i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

class TestParametrized : public testing::TestWithParam<int> {
  protected:
    int foo(int x) { return (x + 3) % 5 == 0; }
};

TEST_P(TestParametrized, Test) {
    int x = GetParam();
    EXPECT_TRUE(foo(x));
}

INSTANTIATE_TEST_SUITE_P(InstantiationName, TestParametrized,
                         testing::Values(2, 4, 6, 8));