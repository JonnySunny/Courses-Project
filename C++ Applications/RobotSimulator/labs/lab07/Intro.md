# Lab07 Google Unit Test
#### Due date: Wednesday, October 25th at 11:55 p.m.
#### Remember to sign in today.
***

## Objective:
1. To master the skills of writing and running your own Google unit tests
2. Understand how to run the unittests so that you can use the project's unittests to thoroughly test your iteration 1
   requirements (i.e. priority 1, priority 2, and priority 3 coding changes)

## Preparing for the Lab
1.  Pull from the public-class-repo repository.
2.  Copy the public-class-repo/labs/lab07 to your own local repository. 

## Materials:
In the lab07/src folder, we have
1. **QuackBehavior.h**, including class *QuackBehavior*, class *Quack*, class *Mute*, class *Squeak*, class *Honk*;
2. **FlyBehavior.h**, including class *FlyBehavior*, class *FlyWithWings*, class *NoFly*, class *FlyWithRocket*;  
3. **Duck.h**, including class *Duck*, class *Mallard*, class *RubberDuck*.

In the lab07/tests folder, we have three unit test files.  They are Duck_Test_Example.cc, FlyBehavior_Test_Example.cc, and QuackBehavior_Test_Example.cc

## Google Test Introduction:
Google C++ Testing Framework helps you write better C++ tests. No matter whether you work on Linux, Windows, or a Mac, if you write C++ code, Google Test can help you. For more information please refer to the following link:
https://github.com/google/googletest/blob/master/googletest/docs/Primer.md.

For this lab, we have set up the environment on the **CSELab** computers, so you can run the tests directly on **CSELab** computers.  We are using the same Google Framework as the project.  You may see some source files in the lab07/src that are from the project.  We do not use these but you could if you wanted to try and write a test for this code.


## Statements:

1. **Test naming**: Please use TEST(classnameTest,methodname), e.g. *TEST(QuackTest, Constructor)*.

2. **File naming**: Please use Filename_classname_unittest.cc, eg:*QuackBehavior_Quack_unittest.cc*.

3. **Assertion type**: Unless the program should not proceed if the test fails, then use EXPECT, not ASSERT.

4. **Comments**: If you have multiple assertions in a single test, then it would be good to add comments to the assertions fail, e.g.  *EXPECT_STREQ("Quack at 10 decibels.",my_quack.quack().c_str())<< "FAIL:Quack Constructor!"*.   The comment follows the test with a **<< "message goes here".**

5. **Test scope**:  Each test should only test a single method/function. In addition, if there is a lot of functionality within that function, it might even be appropriate to separate into different tests.

6. **Test coverage**: Think carefully about what tests should be testing.


## Google Unit Test Examples:

Before trying to write your own unit tests, the following are three simple examples of unit tests that have already been written for you:

```c++
TEST(RubberDuckTest,display){
  RubberDuck my_ralph;
  string except_str="I am a Rubber Duck.";
  ASSERT_STREQ(except_str.c_str(),my_ralph.display().c_str()) << "FAIL: display" ;
}
```
In this unit test, we test the *RubberDuck* class and be more specific, we test its *display function*.

```c++
TEST(FlyBehaviorTest, fly) {
  FlyBehavior my_flybehavior;
  string expect_str="Generic Flying at 5 mph.";
  EXPECT_STREQ(expect_str.c_str(),my_flybehavior.fly().c_str())<< "FAIL: fly function!";
}
```
In this unit test, we test the *FlyBehavior* class and be more specific,  we test its *fly function*.

```c++
TEST(QuackTest, Constructor) {
  Quack my_quack;
  string expect_str="Quack at 10 decibels.";
  EXPECT_STREQ(expect_str.c_str(),my_quack.quack().c_str())<<"FAIL: Quack Constructor!";
}
```
In this unit test, we test the *Quack* class and be more specific, we test its *constructor*.

## How to run Google Unit Test:
1.  You should be in the lab07 directory.
2.  Run *make*
3.  Change the directory to the /build/bin under the lab07 directory
4.  Run the unittests file


## Your Assignments for this lab:
Now, you are ready to write your own tests！  Write the following unit tests for this lab:
1. Write unit tests for class *Squeak*, it should test its constructor and the quack function.

2. Write unit tests for class *FlyWithRocket*, it should test its constructor and the fly function.

3. Write unit tests for class *Mallard*, it should test its constructor and display function.  (Note:  The type needs to be a pointer to a Duck to test polymorphism.)(Hint: To test constructor, you should test the performFly(),performQuack(),setFlyBehavior(), and setQuackBehavior().)

4. Write unit tests for class *RubberDuck*, it should test its constructor and display function.(Hint: To test constructor, you should test the performFly(),performQuack(),setFlyBehavior(), and setQuackBehavior().)

5.  Update the Makefile as needed in the /tests directory and run make from the /lab07 directory.

6.  Run the unittests file in the /lab07/build/bin directory to ensure everything passes the tests.  If something fails, you will need to fix the code.

7.  Push your changes to GitHub.  This should push up all new test .cc files and the Makefile changes.
```
git add .
git commit -m “Submitting Lab07”
git push
```

