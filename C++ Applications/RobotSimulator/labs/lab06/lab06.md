# Lab Session 6: gdb Backtraces
#### Due date: Wednesday, October 18th at 11:55 p.m.

<hr>

In this lab, you will learn how to
- generate the automated doxygen documentation.
- use gdb backtracing to debug C++ programs

Please follow the setup instructions below.

#### Setup
1. Log into a computer in the lab.
2. Open a terminal window.
3. Navigate to your 3081 class repo.
4. _pull_ to get lab06 base code
5. Copy the directory into your labs directory in your individual class repo.
6. Push changes to your student repo.

<hr>

### Doxygen

**Reference**: http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdmainpage

Doxygen scans header and source files for specially formated comments to assemble web page documentation, UML, and or pdfs (via latex). The configuration file was already included in the project folder of the class repo.

Your first task is to generate the documents.

- Navigate to /project/iteration1.
- Run the command: `$ doxygen docs/Doxyfile`
> Make sure you are in the iteration1 folder. The _docs_ folder already exists, and when you run doxygen from the iteration1 folder, that existing directory will get populated with the documentation.
- Look in `/docs` and you should now see a folder `html`
- In the html folder, open _index.html_ with your favorite browser.

Notice that the main page is blank. Let's fix that.

- Navigate to your `/src`. Create a file 'mainpage.h'
- Put this in the file:

```
/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */
 ```

- Replace "This is the introduction" with the paragraph that you wrote and included with your UML submission.
- Save and close.
- Navigate back to `/iteration`
- Run the command `doxygen docs/Doxyfile` and see the results in index.html
- Push your changes.

<hr>

### Debugging with GDB

1. First, build the example program with _make_.
2. Then, run the program:
    ````
    ./date.
    ````
See that the program quits in a Segmentation Fault. In the following steps, we will try to diagnose the problem.

3. Start a debugging session on an executable file by typing _gdb -YOUR-EXECUTABLE-NAME-HERE_
    ````
    gdb date
    ````

4. Once in the debugger session (the prompt will change to (**gdb**)). Then, execute the program with _run_.
5. The program _date_ will run and crash with the following output (your output may look slightly different):
    ````
    (gdb) run
    Starting program: /home/it11/half0032/workspace/S11C3081-user110/lab08/DateCrash/date
    ... A set of Dates ...

   Program received signal SIGSEGV, Segmentation fault.
   0x0000000000401349 in doInterestingThing (yr=1998) at main.cpp:21
   21        *array_len = 4;
    ````

6. Attempt to discover where (and why) in the provided code, the fault is occurring.
In this case, the line number causing the error is provided. If the location is not in the provided code, use the _gdb bt_ command (bt stands for "backtrace") to determine where the fault occurs. Type _bt_ now to see the where the execution stopped in each method:
    ````
    (gdb) bt

    #0  0x0000000000401349 in doInterestingThing (yr=1998) at main.cpp:21
    #1  0x00000000004018bc in main () at main.cpp:54
    ````

The backtrace shows that execution stopped in the method _doInterestingThing()_. This method was called from _main()_ on line 54 of _main.cpp_.

The above backtrace indicates that the error happened on line 21 of _main.cpp_. Edit the file, and look at line 21. Why is this causing an error?

Fix this error by modifying the code in _main.cpp_. Recompile _date_ with _make_, and run the program again.

There are several causes of "segentation faults" in this program. Use _gdb_ to help to identify and fix each issue until it runs correctly (see step 7). You might find the commands _up_ and _print_ particularly useful.

7. When your program is running correctly, running should output the following:
    ````
    ... A set of Dates ...
    default date is: January 1, 1900
    date d2 is: April 19, 1998
    date d3 is: April 19, 1998
    ... Now print out 4 dates in reverse time order ...
    date is: January 1, 1993
    date is: January 1, 1992
    date is: January 1, 1991
    date is: January 1, 1990
    the first date is: January 2, 1990
    ... A set of Dates ...
    default date is: January 1, 1900
    date d2 is: April 19, 1999
    date d3 is: April 19, 1999
    ... Now print out 4 dates in reverse time order ...
    date is: January 1, 1993
    date is: January 1, 1992
    date is: January 1, 1991
    date is: January 1, 1990
    the first date is: January 2, 1990

    ... Goodbye ...
    ````

#### Turning in Lab 6

- mainpage.h exists
- generated doxygen files are not in the repo (shouldn't have to do anything, as the .gitignore already set up for this).
- date executable runs without crashing
- no object code or executable is pushed to the repo

Check in to your personal repository:
    ````
    git add .
    git commit -m “Submitting Lab06”
    git push
    ````

#### References
Using _gdb_ in your own programs
1. Make sure that the debugging symbols are being generated when you compile your programs.
To do this edit the _Makefile_. For all lines calling _g++_ add the flag __-g__.
   ````
   g++ -g -o WHATEVER_FILES_COME_AFTER_GO_HERE
   ````
2. Then do a _make clean_ and recompile. Then you can run _gdb_ on your executable.

#### Commands
The following is a basic set of commands for use with _gdb_. We have highlighted the ones that will probably be most useful for you.

###### unix level commands -- entered at the $ prompt:

| Command | Description |
|---|---|
| man gdb | to get help on gdb at the unix command level |
| g++ -g -o program filename.cpp | to compile & link with the debug (-g) option |
| gdb _ProgramName_ | to execute the debugger on executable _ProgramName_ |


###### Basic gdb commands -- entered after the (gdb) prompt:
| Command | Description |
|---|---|
| help | to display a list of gdb commands |
| help _command_ | to get help on a specified gdb command |
|run | to run/execute the program starting from the beginning |
| backtrace | show the current stack (which function is being executed) |
| up | move up in the backtrace stack |
| down | move down in the backtrace stack |
| continue | to resume running/executing the program |
| next | to execute the current statement and stop at the next statement |
| step | same as next, but step into a function |
| list xx | list source lines starting at line xx |
| list | to list the next source lines |
| list xx,yy | to list sources lines from line xx to line yy |
| list filename:xx | to list source lines in the specified file starting at line xx |
| quit | to quit gdb and revert to the unix command level |
| break _functionname_ | to set a breakpoint at the start of a function (set this before typing run) |
|break classname::functionname | to set a breakpoint at the start of a member function |
| break filename:xx | to set a breakpoint at line xx in the specified file |
| break xx | to set a breakpoint at line xx in the current file |
| break 1 | to set a breakpoint at the first line in the current file (declaration or executable statement) |
| info break | to list all breakpoints (including those disabled); breakpoints are numbered #1, #2, #3, etc. |
| disable xx | to disable breakpoint #xx |
| enable xx | to enable breakpoint #xx |
| print v1 | to print the value of a specified variable |
| info source | to show the name of the current source file |
| info locals | to show local variables in the current frame |
| info sources | to list the name of all source files in use |
| set variable = value | to assign a new value to a specified variable |
| (return) | to re-execute the previous gdb command; this is particularly useful if the previous gdb command was next or step |

You can also execute most gdb commands by entering only the first letter of the command.

* The original source for this list is [here](https://www.bgsu.edu/arts-and-sciences/computer-science/cs-documentation/using-the-gdb-debugger.html).

##### GDB Resources
There are many places to find additional documentation on GDB:

Command reference:   (http://www.yolinux.com/TUTORIALS/GDB-Commands.html)

Another tutorial: (http://www.cs.cmu.edu/~gilpin/tutorial/)

Search for "gdb tutorial" on the web: (http://lmgtfy.com/?q=gdb+tutorial)
