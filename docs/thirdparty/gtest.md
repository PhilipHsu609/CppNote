---
title: "Google Test"
---

# Google Test

C++ testing framework.

## Basic Test

```cpp
#include <gtest/gtest.h>

TEST(TestSuite, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}
```

## Assertions

| Fatal | Non-Fatal | Verifies |
|-------|-----------|----------|
| `ASSERT_TRUE(cond)` | `EXPECT_TRUE(cond)` | condition is true |
| `ASSERT_FALSE(cond)` | `EXPECT_FALSE(cond)` | condition is false |
| `ASSERT_EQ(a, b)` | `EXPECT_EQ(a, b)` | `a == b` |
| `ASSERT_NE(a, b)` | `EXPECT_NE(a, b)` | `a != b` |
| `ASSERT_LT(a, b)` | `EXPECT_LT(a, b)` | `a < b` |
| `ASSERT_LE(a, b)` | `EXPECT_LE(a, b)` | `a <= b` |
| `ASSERT_GT(a, b)` | `EXPECT_GT(a, b)` | `a > b` |
| `ASSERT_GE(a, b)` | `EXPECT_GE(a, b)` | `a >= b` |
| `ASSERT_STREQ(a, b)` | `EXPECT_STREQ(a, b)` | C strings equal |
| `ASSERT_STRNE(a, b)` | `EXPECT_STRNE(a, b)` | C strings not equal |

- `ASSERT_*` - fatal, stops test on failure
- `EXPECT_*` - non-fatal, continues test on failure

## Test Fixtures

Share setup/teardown across tests:

```cpp
class TestFixture : public testing::Test {
  protected:
    void SetUp() override {
        v1 = {1, 2, 3};
        v2 = {1.0, 2.0, 3.0};
    }

    void TearDown() override {
        // cleanup (optional)
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
```

## Parameterized Tests

Run same test with different inputs:

```cpp
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
```

## Key Points

- `TEST()` for simple tests
- `TEST_F()` for fixture-based tests
- `TEST_P()` for parameterized tests
- `ASSERT_*` stops on failure, `EXPECT_*` continues
- `SetUp()`/`TearDown()` for fixture lifecycle

## See Also

- [fmt](fmt.md) - output formatting in tests
