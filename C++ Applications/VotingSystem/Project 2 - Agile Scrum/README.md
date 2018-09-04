# Project 2 - Agile


## Team Members
- Raheel Qureshi (qures037)
- Yuanzong Zhang (zhan3790)
- Zhongyi Sun (sunx0725)
- Ziyi Wang (wang5472)

**All team members worked on debugging of the program together**

---

## New Changes from Ver 1.0
- Plurality now picks winners at random if 2 or more candidates have the same number of votes
- Shuffle is defaulted, but can be turned off for testing by passing in the flag ```-noshuffle``` as first or second argument.
- Change the format for the CSV file. The first line is the choice of algotrithm, the second line is the number of winners. Implemented some error checking on format.
- When runing STV algorithm, ballots are discarded if they contain less rankings than half the candidates running. Discarded ballots are kept track of and logged.
- Along with the full, detailed report, the program now generates a shorter, expedited report containing only the most relevant and pertinent information. Includes information about selection date, type of election, candidates, number of seats, the winners of the election, and so on...


## Issues
- Originally, we planned for our error checking on the new format of including the algorithm and number of winners in the ballot itself to be more robust. If it detected an error or incorrect format, it would inform the user and prompt for proper input of that field. Unfortunately we did not have enough time to implement it as we were having difficulty with it working correctly.

---

## Test files
- examplefile and examplefile1 is in original format.
- eamplefile2,3,10,11,12,13 are in new format and 11 and 12 should give error messages.
- examplefile4-9 are test files for project 1, should act the same way as in project 1.

### Ballot Generator
Included in _testing/Ballot_Generator_ is the executable **Ballot_Generator** that allows for ballot generation of sizes with up to 52 candidates and up to 100,000 ballots for testing. The name of the output file is _Ballot.csv_.
- Run with command ```./Ballot_Generator```
- It will prompt for various parameters, such as number of candidates running, algorithm to use, number of winners, and number of ballots. The max size is 52 candidates and 100,000 ballots.
- Creates an output test CSV files named _Ballot.csv_
    - Directory structure:
        - _src/_ - Source code and simple make file to compiler (`make` and `make clean`)

---

## Compiling and Running the Program
**Compiled using G++ Version 4.9.2 or greater**
- Run `make -j` to build executable
- Run `./Vote_Counter`. It can be supplied the optional argument _\<path-to-CSV-file\>_ and the optional flag _-noshuffle_
- If no pathname is supplied, the program will prompt for a valid CSV file to open

---

- Note: make sure the csv file is in the same directory with the executable file, or enter the full directory for the csv file
- The _-j_ flag in make allows for multi-process compilation, speeding up the build process

- Run '_make utest -j_' to make unit tests in _tests/_ folder
- Run '_Unit\_Tests_' executable to run the unit tests (this command need to run inside tests folder)

- Run '_make stest -j_' to make unit tests in _tests/_ folder
- Run '_System\_Tests_' executable to run the unit tests (this command need to run inside tests folder)

- Run '_make clean_' to clean directory and erase all generated build folders and program files

---

## Program Design
- There are in total 6 classes in the program: Ballot, Candidate, Algorithm, Plurality, STV, and the main function.
- Ballot class is used to store the information of one single ballot, we use a map to store information, which will use voters' preference values as keys and candidates' names as values
- Candidate class is used to store candidates' names and the ballots that got assigned to them
- Algorithm is used as an interface which the Plurality and Droop Quota algorithms instantiate through inheritance
- Plurality class is used to generate result using Plurality algorithm, basically it loop through all ballots and decide which candidates got most votes
- STV algorithm is used to generate result using Droop Quota algorithm, it is a recursive function, which continued calling itself until the seats needed been filled.
