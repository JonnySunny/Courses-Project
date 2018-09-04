/**
 * @file algorithm.h
 *
 * @copyright Spring 2018 CSci 5801 Team 10, All rights reserved.
 */

#ifndef SRC_ALGORITHM_H_
#define SRC_ALGORITHM_H_

// Includes
#include <string>
#include <sstream>  // For stringstream
#include <fstream>  // For file stream
#include <vector>
#include "./ballot.h"
#include "./candidate.h"

/**************************************************************************/

/**
    @brief This is the base class of algorithms. It acts as an interface class that must be instantiated through one of its children.
 */
class Algorithm  {
 public:
    Algorithm(std::vector<Ballot> b, std::vector<Candidate> c, int s = 0) :
        ballot_list(b),
        candidates_list(c),
        seats(s) {}

    virtual ~Algorithm() {
        ballot_list.clear();
        candidates_list.clear();
    }

    // Getters
    const int get_Seats() {return seats;}
    std::vector<Ballot> get_Ballots() {return ballot_list;}
    std::vector<Candidate> get_Candidates() {return candidates_list;}

    /**
        @brief Abstract method, must be defined in child.
        The main driver function, runs the corresponding defined algorithm to determine winners and losers.
    */
    virtual void run() = 0;

    /**
        @brief Abstract method, must be defined in child.
        Prints the winners of each seat from the election to cout.
    */
    virtual void printResults() = 0;

    /**
        @brief Generate report and dreakdown of program execution. Puts report in same folder as program executable.
    */
    virtual void generateReport() {
        // std::cout << "\n\n\n" << report.str() << "\n\n";

        std::ofstream output;
        output.open("Report.txt");
        output << report.str() << std::endl;
        output.close();
    }


 protected:
    /*
        These are protected because they need to be extensively accessed and manipulated by child classes.
    */

    // Temporary buffer to hold information for report
    // Added to as the program executes
    std::stringstream report;
    // List of ballots
    std::vector<Ballot> ballot_list;
    // List of candidates
    std::vector<Candidate> candidates_list;


 private:
    int seats;  // Seats to be filled
};

#endif  // SRC_ALGORITHM_H_
