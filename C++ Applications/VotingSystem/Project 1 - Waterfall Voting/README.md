# Project 1 - Waterfall Voting

## Team Members and Contributions
- Raheel Qureshi (qures037): Worked on STV class of the program, makefile and cpplint. Also worked on code refinement, input handling, and sanity checks.
- Yuanzong Zhang (zhan3790): Worked on Ballot, Candidate, and Main classes of the program, as well as the README.
- Zhongyi Sun (sunx0725): Worked on Algorithm Interface and Plurality class of the program.
- Ziyi Wang (wang5472): Worked on the doxygen, inline comment, and other documentations.

**All team members worked on debugging of the program together**

---

## Compiling and Running the Program
- run 'make' command in the terminal inside the file directory
- then run './Vote_counter' inside the same directory can also along with filename for example  './Vote_counter examplefile.csv"
- after the executable running, enter the name of the csv file
- then enter the number of seats to fill and choose an algorithm to use
- Note: make sure the csv file is in the same directory with the executable file, or enter the full directory for the csv file
- run "make tests" to make tests and "make tests clean" to delete them
- run './Unit_Test' to run the test file (this command need to run inside tests folder)
=======
**Compiled using G++ Version 5.4.0 or greater, will NOT compile on G++ 4.9.2**
1. Run '_make -j_' command in the terminal inside the file directory to build executable
1. Run '_./Vote\_Counter_'. It can be supplied the optional argument _\<path-to-CSV-file\>_
1. Follow prompts in program

- Note: make sure the csv file is in the same directory with the executable file, or enter the full directory for the csv file
- The _-j_ flag in make allows for multi-process compilation, speeding up the build process

1. Run '_make tests -j_' to make unit tests in _tests/_ folder
1. Run '_Unit\_Tests_' executable to run the unit tests (this command need to run inside tests folder)

- Run '_make clean_' to clean directory and erase all generated build folders and program files

- Run "make tests" to make unit tests in tests/ folder and "make clean" to clean directory of all generated files
- run Unit_Tests executable to run the unit tests (this command need to run inside tests folder)
---

## Program Design
- There are in total 6 classes in the program: Ballot, Candidate, Algorithm, Plurality, STV, and the main function.
- Ballot class is used to store the information of one single ballot, we use a map to store information, which will use voters' preference values as keys and candidates' names as values
- Candidate class is used to store candidates' names and the ballots that got assigned to them
- Algorithm is used as an interface which the Plurality and Droop Quota algorithms instantiate through inheritance
- Plurality class is used to generate result using Plurality algorithm, basically it loop through all ballots and decide which candidates got most votes
- STV algorithm is used to generate result using Droop Quota algorithm, it is a recursive function, which continued calling itself until the seats needed been filled.
