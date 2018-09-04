/* STUDENTS: Write your own unit tests in this file.  Or, better yet,
   rename this file to something more meaningful and/or add additional
   files of tests to this directory to test your project code in
   whatever ways you see fit!
 */

// The Google Test framework
#include <gtest/gtest.h>


// Includes for project code in the ../src directory
#include "../src/arena.h"



TEST(StudentTests, SanityCheck) {
  EXPECT_EQ(1, 1);
}

// make sure the simtime is initialized to 0.0 whenever a new RobotLand is created
TEST(StudentTests, SimTimeInitialized) {
  //Arena rl;
  //EXPECT_EQ(rl.get_current_time(), 0.0);
}
