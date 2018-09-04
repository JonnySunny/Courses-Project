#### Lab Session 3: Introduction to Makefiles

**Due date:** Wed, Sept. 27th at 11:55 pm

-   Makefile

In this lab, you will write a Makefile in order to make compilation of our duck simulator convenient. Please follow the setup instructions below.

 ##### Getting Started and Words of Advice

The starting code base for this lab exercise is available in the class repo:
https://github.umn.edu/umn-csci-watters-3081F17/public-class-repo. You do not want to edit within the class repo or it will cause merge conflicts. Copy the code to your individual repo and work within that. Please follow the same directory structure such that lab03 is within the labs folder.

At each push, an automatic feedback file will be pushed to your repo.
> Don't forget to _pull_ the feedback before making more edits to your repo or you will cause merge conflicts.

The automated feedback encompasses a majority, if not all, the tests that will be used to grade your lab. Please make sure you review the feedback from your final submission to ensure it passes all the tests. Minor fixable errors can result in 0 points for the lab because automated grading fails. You are responsible for ensuring your code passes all tests in the feedback.

> We will not reconsider your lab grade after the due date if the feedback file gave you information that you ignored.


##### Step 1: Update Your Repositories


1. Open a terminal window.
3. Navigate to the directory of your 3081 class repo.
1. `git pull` to get lab03 base code
1. Copy the directory into your _labs_ directory in your individual class repo.

   ``` cp -R public-class-repo/lab03 <path_to_individual_repo>/labs/.```

1. Navigate into the lab03 directory in your individual repo:

#### Instructions

A Makefile is a build system. The main difference between a script file and a Makefile is that a Makefile keeps track of file modification timestamps. Some consider the Makefile to be a glorified script but to call it that makes it sound like it is simple to do. Makefiles can be quite complex.

##### Create Your Makefile

1.  Create your Makefile.
2.  **emacs Makefile &**
3.  Create build and link targets for all the files in the lab03 directory. (*See “Targets” section in Makefile Cheat Sheet below*.)
    Hint: In listing the targets, dependencies, and compiler actions, think carefully about the relationships among the classes. Note: Name your final executable as `lab03.out`.
4.  Create a “clean” target which deletes the .o files and the executable (*See “Dummy Targets” section in Makefile Cheat Sheet below.*)
5.  As you are developing the Makefile, test to make sure ```make``` and ```make clean``` both do what is expected.

##### Test Your Makefile

1.  Clean your project: ```make clean```
2.  Build your project: ```make```

##### Improve Your Makefile

1.  First, copy your makefile so that you have a backup: cp Makefile MakefileOld
2.  Modify your Makefile to add a variable. For example, create a variable called CXX that defines the name of the compiler to use. Update the targets to use this variable (*See “Macros” section in Makefile Cheat Sheet below.*)
3.  Simplify your MakefileVar by editing it to use variables and pattern rules for the build and link targets (*See “Macros” section in Makefile Cheat Sheet below.*)
4.  If you wish to build using the old Makefile, you can do so by running: make -f MakefileOld

##### Build and Submit

1.  Clean and build your program with your Makefile
2.  Run your program
3.  ```./lab03.out```
4.  Commit and check in results:
5.  git add .
6.  git commit -m “finishing lab03”
7.  git push origin master


#### Makefile Cheat Sheet

##### Targets

A Makefile target works in this way:
```
target: dependencies
[tab] system command
```
A target is usually a file, but not always. This definition tells you to construct the target when the dependencies are newer than the target with the system command. For example, to compile our duck simulator you could enter the following in your Makefile:

```
Duck.o: Duck.h Duck.cpp
    g++ -c Duck.cpp
```

##### Dummy Targets

There are times when you do not want to create a target, but instead run a few commands. For example, you may want to “clean” your directory of files that come from the compilation process. This could be done with the following:
```
clean:
    rm *.o *.out
```

##### Macros

A macro is a “variable” can be defined in a Makefile. Macros are defined as = pairs and can be called by either \$(VARIABLE\_NAME) or \${VARIABLE\_NAME}. For example, we can define compiler and compiler flags macros:

```
CXX = g++
CXXFLAGS = -Wall -c -std=c++11
```

(Makefile conventions say variable names should consist of all caps andunderscores)
