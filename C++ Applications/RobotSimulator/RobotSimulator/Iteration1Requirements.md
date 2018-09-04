
>Your software is a reflection of your understanding of the requirements as specified in this document. If you do not understand any portion of the requirements or you think that the requirements are underspecified, it is your responsibility to get clarification from the instructor or a TA. Please read this document carefully and review it prior to turning in your iteration for assessment.

# Robot Simulator: Iteration 1

<span style="color:red">

| Date | Item | Description |
|:----:|:-----|:------------|
| Wed, Oct 11, 10pm | UML diagram of base code | submit via Github |
| Wed, Oct 25, 10pm | Preliminary code tests   | Pass automated tests |
| Wed, Nov 1, 10pm | Documentation and Code Implementation | Automated tests and inspection |

</span>

Your project should demonstrate thoughtful software development with good design quality, using good process. This iteration will help you to establish those good habits. Unit tests will be provided for automated testing of functionality. You will create design documents including a UML diagram. _doxygen_ will be used to automatically generate code documentation. Code style will comply to the Google Style Guide. Intermediate deadlines will keep you on track in this iterative process.

#### Deliverables and Submission Process

Everything will be submitted via Github. We will pull your repository at the specified due dates and grade according to the contents at that time.

> Please verify that your submission compiles on a cselabs machine and it is complete. There are many components to be submitted - a checklist has been provided.

The schedule is very tight, and it is important that you keep up with the project. The project will continue to build throughout the semester, and if you get behind, it will be very difficult to catch up. For this reason, **late assignments will not be accepted**, but you will receive partial credit for partial completion of the requirements.

You can convert this requirements document to pdf using this tool: http://www.markdowntopdf.com/

<hr>

## Documentation and Code Implementation Requirements

### Overview

The goal of this software project is to develop a rudimentary robot simulator in which robot behavior is visualized within a graphics window. The exact use of the application is yet to be determined. It might be that it is used more like a video game in which users control the robots. Alternatively, it might be a test environment for experimenting with autonomous robot control using sensor feedback, or it might be a visualization of real robots operating in a remote location. Due to the ambiguity of future use, it
is important that you plan for change through good design.

In this iteration, you will put all the pieces in place for development including libraries, base code, unit tests with Google Test, class structure, Google style guide compliance, design documentation using UML, and doxygen documentation. Teaching staff will also be working diligently to provide the structure and support for development, testing, and documentation. Automation in unit testing, style compliance, in-house github testing, and documentation will make this an easier process, however it means that you will have to develop within the constraints of these systems. Often there is a learning curve and a lot of systems trouble-shooting to get it all working, so start early!

In the first iteration, the robot simulator is more like a video game. Users control the robot with the arrow keys. The objective of the game is to reach a moving home base before running out of energy. Energy is depleted as the robot moves and even more when it bumps into obstacles, but can renew its energy by going to the charging station.

### Functional Requirements

You are being provided with a significant initial code base. The first iteration is focused on enhancing
functionality and getting practiced in the software development process. It is also a drop into the depths
of C++ syntax. If you have any questions about the provided code, please ask. We do not expect you to understand all the constructs in this code. Below is an outline of the required functionality.

The code is organized such that robot behavior is separate from robot visualization, which allows for automated unit testing using Google Test. For example, if the robot is supposed to move from {x1,y1} to {x2, y2}, the member _position_ should be set to {x2, y2} when complete, which is easy to check in an automated way with "getters." The visualization of that move in the graphics window can only be tested through human inspection.
The Robot class is composed of many other classes that control various aspects of robot behavior and environment interaction. You will need to maintain this class structure to interface with Google Tests.

#### Robot Arena

The robot arena has a robot, obstacle, home base, and charging station. The intent is for the robot
to move around the space in search of the home base. As it moves, its battery is depleted.
The robot can refill its battery by touching the recharge station.
If it bumps into something, it should bounce off of it. The user can change the speed and
direction of the robot using the arrow keys. If the robot reaches the home base, you win.
If it runs out of battery, you lose. All of this functionality is not yet implemented.

#### Graphics Environment

The graphics environment consists primarily of a single window with robots, obstacles, home base, and charging station. All objects in the environment will be drawn as circles, which greatly simplifies collision detection. You are welcome to add graphics enhancements, such as color, text, or decorations provided it does not interfere with required functionality. The basic graphics window framework has been provided. You will need to get familiar with the graphics library and provided code to learn how to draw objects of particular shape in the environment.


#### GUI and User Input

A basic GUI with user buttons and input via mouse and keyboard has been provided. The user should have the following control:

- With UI buttons: Restart and Pause
- With left and right arrow keys, change the direction of the robot
- With up and down arrow keys, change the speed of the robot (no reverse)

<hr>

**REQUIREMENTS you need to fulfill**

> This is just functionality. Along the way, please document the code using
Doxygen syntax and test for Google Style compliance using cpplint.

The iterative method identifies and prioritizes feature enhancements and code refactoring
over short intervals called sprints. Below is a prioritized list of feature
enhancements, fixes, and refactoring of the code. **Complete all functionality in
one priority level before moving on to the next.** In this way, if we run out
of time, the low priority items will be dropped from the requirements.

- Priority Level 1
  - Implement the arrow keypress handlers. Translate the keypress into appropriate
  command for the robot arena and send the command to the arena, which
  will send the command to robot_motion_handler_.
      - Up arrow increases speed, up to a defined limit
      - Down arrow decreases speed, down to 0 (no negative speeds)
      - Right arrow changes the heading clockwise by some delta of your choosing
      - Left arrow changes the heading counter-clockwise by some defined delta
  - Bounce robot off of other entities (at angle of incidence).
  - Deplete battery as robot moves.
  - Recharge battery if robot collides with recharge station.
  - Home base is mobile.

- Priority Level 2
  - Implement functionality for pause and restart buttons.
  - Implement functionality for win and lose.
  - Fix bounce behavior off of left and right walls (it should reflect at angle of incidence.)
  - Visualize battery level (can be through GUI or something on the robot)
  - Replace all nanogui::Color types in Arena to separate graphics from robots. Devise a system
  that will convert Arena color to nanogui color.

- Priority Level 3
  - Limit the working dimensions inside which the robots can move (so GUI is not in arena).
  - Create a Sensor base class and make SensorTouch a subclass.
  - Deplete battery when robot bumps into obstacles.
  - Slow the robot down when it bumps into obstacles.
  - Home base randomly changes direction at random times.
  - Create a total of 5 obstacles in the environment.

<hr>

### Unit Testing with Google Test

https://github.com/google/googletest

Unit tests are essential in a large-scale project, because the entire code base can be tested regularly, automatically, as it undergoes development. In the strictest application of Test-Driven Development (TDD), the tests are written _before_ the code, which helps solidify requirements and write testable code.

While not strictly TDD, the provided code for this project iteration includes tests written in Google Test. The functionality of the various functions and class methods must pass each of these tests (which are a subset of the complete tests used for assessment) to receive full credit. **Note what was just stated: these are a subset of tests used for assessment, thus also write and use your own tests.**

The provided makefile allows you to include only the tests for which you have implemented functionality. In the makefile uncomment collections of tests when you are ready. In addition to Google Tests, the github tests will provide a feedback file at each push to the repo. The tests run through github will run the unit tests as part of automatic feedback.

_More to come on testing_.

### File Structure

You must follow the file structure provided. It follows the conventions of code development, with some specific requirements added as part of the Google style guide. Not being compliant with the structure will likely break compilation and testing. Even if it doesn't, you will lose points for not maintaining the provided file structure.

### Google Style Guide Compliance

https://google.github.io/styleguide/cppguide.html

Consistency in code organization, naming conventions, file structure, and formatting makes code easier to read and integrate. There are many options with various merits, so it is up to the development team to establish these conventions, or in the words of Kevin Wendt "The only style guide that really matters is the one your boss uses." We decided to use the Google style guide because it is published, documented, and has automated tests. We don't agree with every decision, but we are complying so that we are all coding to a single standard.

To test your code for Google style compliance, install cpplint  (https://github.com/google/styleguide/tree/gh-pages/cpplint) using pip3 installer
```
pip3 install cpplint
```
and to test your code, at the command line use
```
python3 <filename>
```
Obviously, if you are doing this on your own laptop you need Python 3.x installed.

<hr>

## Documentation

Code documentation comes in many forms for many audiences. For this project, your audience is other programmers, who need to understand class interfaces, function parameters, function behavior, code organization, class organization, and code logic. Self-documenting code (i.e. using good organization and naming conventions) is an efficient means of communicating, since you have to write the code anyway. _Good_ comments - not too much, not too little - help guide others through the logic and class interfaces. For the larger picture of code and class structure, use UML diagrams and Doxygen-generated (automatic) web pages.

Doxygen automatically generates documentation of class and code structure when you follow some simple conventions for commenting within your code (_see_ http://www.stack.nl/~dimitri/doxygen/). _More on Doxygen soon_.

All of these elements of documentation will be assessed, accounting for half of your grade for each iteration. Think about these two extremes: 1) your code functions perfectly and you have almost no documentation - you will likely fail on this iteration; 2) your code is not functional and will only compile when you comment most of it out, but you have complete, great documentation - you will likely get a decent grade on this iteration. Get in the habit of creating the documentation along with the code.

<hr>

## Assessment

Your software **must compile on a cselabs machine or it will not be graded**. We will not grade your project unless it compiles. As long as you provide a version that compiles, we will evaluate those aspects that are partially functional for partial credit. In other words, <u>comment it out if it breaks compilation</u>.

Your software will be assessed through automatic testing and by the TA. You will receive immediate feedback whenever you push to github (although not now - we will let you know when those scripts are in place). At the deadline, all submissions will be downloaded and the automated testing will no longer be available. Through both automated testing and the TA, the process for testing will be to `make clean` then `make`. We **highly encourage** you to freshly clone your repo on a **cselabs machine** and also `make clean` and `make` to confirm all is working well.

This is the breakdown for point distribution:

- 20% : Iteration \#1
- 05% : UML (base code)
- 05% : UML (your design, draft)
- 10% : Preliminary Code Submission
- 40% : Final Documentation
- 40% : Final Code

### Documentation Assessment ( 50% )

#### Drafts of UML Diagrams ( 10% )

Early in the iteration, you will construct a UML diagram of the provided code, then of the complete code for that iteration. These are drafts of the final product, and we anticipate that they will be revised. We will be looking for proper use of UML components, and a correct depiction of the code structure.

#### Complete Iteration Documentation ( 40% )

#### Design Document

The final design document will include the final UML diagram, as well as an overview of the project iteration. We will look for a well written and well organized document that clearly articulates the design. It must stand alone in the sense that anyone reading it should not have to look at code or other documents to understand the design.

#### Google Style Compliance

We will run the automated test using 'cpplint' to check compliance. There are a few additional elements for compliance that _cpplint_ does not check for, thus TAs will inspect for those.

#### Doxygen Documentation

We will compile the code to generate _Doxygen_ web pages. All classes and major functions must be documented as specified in the _Doxygen_ documentation.

#### Readme.md

The github submission must include a _readme_ that communicates to the TAs. It should report any elements not complete and any known bugs in the system.

#### Self-Documenting Code

TAs will inspect code for good naming conventions, good code organization, and internal comments to highlight logic.

### Code Assessment ( 50% )

#### Preliminary Code Submission ( 10% )

In the week prior to the due date of the completed iteration, we will run a subset of the automated tests. You must pass all tests to receive full points for the preliminary submission. There will be no inspection of the code at this point -- it is strictly a test for completed functionality. There will be transparency in this process in that you will know what functionality will be tested, and you will see the results. Points earned at this stage are independent of the 40% points for the final submission.

#### Completed Iteration Code ( 40% )

Code functionality will be tested with automated tests through Github, which in turn run the automated unit tests of Google Test. The provided unit tests are a subset of the final tests run for this iteration. Review the automated feedback prior to final submission, as it will identify any issues with directory structure, compilation issues, or failed unit tests.

<hr>

## Getting Started

AFTER reading this document, pull the public class repository to obtain the base code. Copy that code to your individual class repository on a cselabs machine while maintaining the file structure. Follow the directions for compilation and start it up!

> **NOTE**: Graphics code has been compiled and made available on the cselabs machines. You are linking with this code, thus it should not appear in your repo. If you want to develop on your personal machine, then you need to recreate this set-up. Do not put this code in your repo.


<hr>

## Resources

Graphics Libraries :
- https://github.com/wjakob/nanogui
- https://nanogui.readthedocs.io/en/latest/
- https://github.com/memononen/NanoVG
- https://www.opengl.org/

Local System and Compilation:
- Repo: https://github.umn.edu/umn-csci-3081F17/class-repo-public
- Linking library: `/project/3081cf17/`
- Compilation: https://gcc.gnu.org/
- Linux quick reference: http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/linux.html
- Makefile Resources: http://www-users.cs.umn.edu/~larson/repo-website-resources/website/examples/csresources/cpp.html

Testing:
- https://github.com/google/googletest
- Unit Testing: https://martinfowler.com/bliki/UnitTest.html

Style:
- https://google.github.io/styleguide/cppguide.html
- https://github.com/google/styleguide/tree/gh-pages/cpplint
- https://www.python.org/downloads/

Documentation:
- http://www.stack.nl/~dimitri/doxygen/
- https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

IDEs:
- Xemacs: https://www.xemacs.org/
- vi: http://www.lagmonster.org/docs/vi.html
- Atom: https://atom.io/
- Sublime: https://www.sublimetext.com/
- Eclipse: https://eclipse.org/
