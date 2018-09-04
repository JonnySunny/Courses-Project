// Google Test Framework
#include <gtest/gtest.h>
// Project code from the ../src directory
#include "../src/FlyBehavior.h"
#include <string.h>

#ifdef FEEDBACK_TEST_05
TEST(FlyWithRocketTest, Constructor ) {
  FlyWithRocket my_flybehavior;
  string expect_str="Fly with wings at speed of 20 mph.";
  EXPECT_STREQ(expect_str.c_str(),my_flybehavior.fly().c_str())<< "FAIL:FlyWithRocket Constructor!";
}

TEST(FlyWithRocketTest, fly) {
  FlyWithRocket my_flybehavior;
  string expect_str="Fly with wings at speed of 20 mph.";
  EXPECT_STREQ(expect_str.c_str(),my_flybehavior.fly().c_str())<< "FAIL:FlyWithRocket: fly function!";
}


#endif
