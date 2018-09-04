# Lab 2 - Compiling and Linking

> A reminder that in Dr. Watters's section, attendance is required for you to receive credit for the lab.

In this lab, you are going to learn how to compile the source code and link the executable. The source code is in .cpp and .h files. The object code is in the .o files. Executables are either .out or have no extension.

In addition to practicing compilation, you will define classes and subclasses. In class exercises, we have demonstrated the basics on class definitions. The syntax of a class and subclass definition is also provided within this document.

Deliverables:
- main.cpp
- DecoyDuck.cpp
- DecoyDuck.h
- lab02_answers.txt (Use this to submit your answers to the highlighted steps.)

In this lab, you will write and edit some C++ code, build it, and run it. Please follow the instructions below. The given source code will help you get started.

### Getting Started and Words of Advice

The starting code base for this lab exercise is available in the class repo:
https://github.umn.edu/umn-csci-watters-3081F17/public-class-repo. You do not want to edit within the class repo or it will cause merge conflicts. Copy the code to your
individual repo and work within that. Please follow the same directory structure
such that lab02 is within the labs folder.

At each push, an automatic feedback file will be pushed to your repo.
> ** Don't forget to _pull_ the feedback before making more edits to your repo or you will cause merge conflicts. **

The automated feedback encompasses a majority, if not all, the tests that will be used to grade your lab. Please make sure you review the feedback from your final submission to ensure it passes all the tests. Minor fixable errors can result in 0 points for the lab because automated grading fails. You are responsible for ensuring your code passes all tests in the feedback.

> ** We will not reconsider your lab grade after the due date if the feedback file gave you information that you ignored. **

Text editors designed for coding are essential. There are many good options available for free and on the cselabs machines. Instructions below use emacs, but
feel free to use your favorite.

(Create lab02_answers.txt before you record your answers)

### Step 1: Update Your Repositories

   _If you did not do last week's lab, refer to lab01 for directions on how to set up git for both the class repo and your individual repo._

1. Open a terminal window.
3. Navigate to the directory of your 3081 class repo.
1. `pull` to get lab02 base code
1. Copy the directory into your _labs_ directory in your individual class repo.

   ``` mv labs/lab02 <path_to_individual_repo>/labs/.```

1. Navigate into the lab02 directory in your individual repo:

#### Step 2: Compile the Source Code

1. Compile the .cpp files into object files.
   ``` 
   % g++ -c -o main.o main.cpp
   % g++ -c -o Duck.o Duck.cpp
   % g++ -c -o MallardDuck.o MallardDuck.cpp
   % g++ -c -o RubberDuck.o RubberDuck.cpp
   ```
   ** What does all this mean?**
   - `g++` : call to the gnu c++ compiler
   - `-c`  : a flag to indicate compilation, as opposed to linking
   - `-o`  : output the results of compilation into the file following this flag
   - `main.cpp` : the last file is the one to be compiled

   _If `-c-` is not provided, the compiler will attempt to compile and link. If `-o` with an output file is not provided, the compiler will use the name of the .cpp file for the .o filename._

   Notice that each file is independently compiled, even though there are interdependencies among them. If you look in the .cpp file, there will be a `#include file.h` statement which essentially inserts the text of <file.h> at the location of the #include statement. Compilation will create symbol tables for all classes, variables, functions declared within those header files, but with no associated address for the definition of those elements. When the files are _linked_, those dependencies will be resolved and the definitions of the various objects will be included in the complete program.

### Step 2: Linking to Generate the Executable

1. Link the object files into an executable: 

   ```% g++ -o duck main.o Duck.o MallardDuck.o RubberDuck.o'''

   ** What does all this mean?**
   - `g++` : call to the gnu c++ compiler
   - `-o`  : output the executable into the file following this flag
   - list of files : all the files that need to be linked.

  _Notice there was no need to tell the compiler that we are in the linking phase. If `-o` with an output file is not provided, the compiler will create the executable `a.out`._

1. Run the program: 

   ```% ./duck```

### Step 3: Add DecoyDuck to Current Project

First, let's review the syntax for class definitions in C++. There is a lot going on this simple class definition for the interface of a generic duck from which we will inherit other classes.
```
#ifndef LAB2_DUCK_H_
#define LAB2_DUCK_H_
...
#endif
```
This serves as a guard for the header file. If there are interdependencies among files such that the compiler is instructed to include this several times, this safeguard communicates to the compiler that this code has already been incorporated. It makes compilation more efficient, and when you have circular references, it is necessary to prevent the preprocessor from infinite file includes.

##### Duck.h

```C++
class Duck {
public:
    Duck();
    virtual void performQuack();
    virtual std::string getDescription() = 0;
};
```

- `Duck() is the constructor with no passed parameters.`
- 'virtual' indicates this can be overwritten by the subclass. When we study polymorphism, the need for `virtual` will become clearer.
- `virtual std::string getDescription()=0` : The `=0` is a special indicator to the compiler that this function MUST be overwritten by the subclass.
- `~Duck() {}` is the declaration and definition of the destructor. A default is created if not specified. It is essential when using dynamic allocation.
- `public:` gives direct access to members and methods outside the class.
- '};' : Don't forget to conclude your definition


##### Duck.cpp

```C++
#include "Duck.h"
```
Don't forget to include the Duck.h file - of course the compiler will let you know if you forget it when it tries to search for the _Duck_ class for inheritance.

```C++
class RubberDuck : public Duck {
public:
    RubberDuck();
    ~RubberDuck();

    std::string getDescription();
    void performQuack();
};
```
- `class RubberDuck : public Duck` is the declaration of a new class RubberDuck that inherits from the class Duck. `public` indicates that RubberDuck will have full access to those elements in the Duck class.
- Notice that all methods of the Duck class are restated here because they will all be overwritten by RubberDuck. Definitions of these functions are in the `RubberDuck.cpp` file.

##### main.cpp

```C++
#include "MallardDuck.h"
#include "RubberDuck.h"
```
Notice that we are not including Duck.h. Can you guess why we don't need it, even though we are referencing it below?

```C++
using std::cout;
using std::endl;

int main() {

    // Create Ducks
    Duck jane;
    MallardDuck maloy;
    RubberDuck lemon;
```

These are the instantiations of the different types of ducks. The beauty of subclasses comes into play when we can treat all types of ducks identically, so that the code chooses the appropriate method for the given type. This is polymorphism, which requires knowledge of pointers and dynamic allocation - soon to be covered.

#### Step 1: Create a New Class

Your task is to add another duck subclass to this simulator, namely the decoy duck. Here is the specification:

<ul><ul>
    <li> Name the class _DecoyDuck_
    <li> The description is "a plastic decoy duck"
    <li> It is silent, thus it says '...'
</ul></ul>

1. Create both a DecoyDuck.h and DecoyDuck.cpp file in your favorite editor (e.g. `atom& DecoyDuck.h`).
1. Define the class as a subclass of _Duck_
2. Declare the needed methods in the .h file as described in the specification.
3. Define the needed methods in the .cpp file.
4. Modify _main.cpp_ to include a DecoyDuck in the simulation.

>Note that you do not need to recompile any of the other files. It is only the linking process that must be redone. This makes compilation far more efficient, which doesn't seem like much of a time savings in our little program, but imagine a project in which the compilation takes hours!

1. Compile your new duck and link it all together.


Submit your DecoyDuck.h, DecoyDuck.cpp, main.cpp, and lab01_answers.txt files to your individual git repository.

### Step 4 : Add MysteryDuck class.

Create _MysteryDuck_ class that inherits from _Duck_. Create a constructor in which the user passes in the description and sound. Add this to _main.cpp_. Compile and link as before. Currently, Duck does not have any members. You will need variables of type string in which to save the description and sound, then use in the methods. Don't forget to hide your members from objects outside the class.


### Step 5 : Push to the repository

```
git add *
git commit -m “adding decoy and mystery duck classes”
git push
```
