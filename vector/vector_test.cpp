#include <gtest/gtest.h>
#include "vector.hpp"

// push_back()

TEST(PushBackTest, Empty) {
  vector v;
  v.push_back(42);
  ASSERT_EQ(v[0], 42);
}

TEST(PushBackTest, HasElements) {
  vector v;
  v.push_back(1337);
  ASSERT_EQ(v[0], 1337);
  v.push_back(42);
  ASSERT_EQ(v[0], 1337);
  ASSERT_EQ(v[1], 42);
}

TEST(PushBackTest, Resize) {
  vector v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(v[i], i);
  }
}

TEST(PushBackTest, Negative) {
  vector v;
  v.push_back(-42);
  ASSERT_EQ(v[0], -42);
}
