// Google Test Framework
#include <gtest/gtest.h>
// Project code from the ../src directory
#include "../src/FlyBehavior.h"
#include <string.h>

#ifdef FEEDBACK_TEST_02

TEST(FlyBehaviorTest, fly) {
  FlyBehavior my_flybehavior;
  string expect_str="Generic Flying at 5 mph.";
  EXPECT_STREQ(expect_str.c_str(),my_flybehavior.fly().c_str())<< "FAIL: fly function!";
}

#endif
