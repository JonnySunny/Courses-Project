/**
* @file plurality.h
*
* @copyright Spring 2018 CSci 5801 Team 10, All rights reserved.
*/

#ifndef SRC_PLURALITY_H_
#define SRC_PLURALITY_H_

// Includes
#include <vector>
#include "./algorithm.h"

// Forward declarations
class Ballot;
class Candidate;

/**************************************************************************/

/**
    @brief The plurality method. Assigns ballots to candidates based on highest preference. Winners are the candidates with the highest vote counts.
*/
class Plurality : public Algorithm {
 public:
    Plurality(std::vector<Ballot> b, std::vector<Candidate> c, int = 0);
    ~Plurality() {}

    /**
        @brief Implementation of abstract function.
        Main function: runs the plurality algorithm to assign votes to candidates. Sorts candidates by decreasing vote count.
    */
    void run();

    /**
        @brief Implementation of abstract function.
        Print the winners of the election.
    */
    void printResults();


 private:
    /**
        @brief Sorts candidates from most votes to least votes.
    */
    void sortCandidates();

    int skipped;    // Number of empty ballots skipped
};

#endif  // SRC_PLURALITY_H_
