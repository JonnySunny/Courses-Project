/**
    @file droop.h

    @copyright Spring 2018, Team 10 CSci 5801
*/

#ifndef SRC_DROOP_H_
#define SRC_DROOP_H_

// Includes
#include <vector>
#include <string>
#include "./algorithm.h"

// Forward declarations
class Ballot;
class Candidate;

/**************************************************************************/

/**
    @brief STV class. Uses a droop quota to determine winners. Makes a winners and losers list
*   after iterating through the candidates list.
*   Sorts every candidate into one of the two lists depending on if they made the quota or not.
*/
class STV : public Algorithm {
 public:
    STV(std::vector<Ballot>, std::vector<Candidate>,
        int = 0, bool = true);
    ~STV();

    // Getters

    /**
    * @brief return the winners list
    * @return vector<Candidate>
    */
    std::vector<Candidate> get_Winners() {return winners;}

    /**
    * @brief return the losers list
    * @return vector<Candidate>
    */
    std::vector<Candidate> get_Losers() {return losers;}

    /**
        @brief Implementation of abstract function.
        Main function: runs the droop quota algorithm to determine the winners and losers. Sorts all candidates into one of those two categories.
    */
    void run();

    /**
        @brief Implementation of abstract function.
        Print the winners of the election.
    */
    void printResults();

    /**
        @brief Find Candidate class by name in the MAIN candidates vector (not winner or loser list).

        @param string: Name to search for

        @return int Index of the candidate's location, or -1 if not found
    */
    const int findCandidateIndexByName(std::string);

    /**
        @brief Add Candidate to winner list.

        @param Candidate: The Candidate to add.
    */
    void addWinner(Candidate);

    /**
        @brief Add Candidate to loser list.

        @param Candidate: The Candidate to add.
    */
    void addLoser(Candidate);


 private:
    /**
        @brief If shuffle option is turned on (default), the ballots will be randomly shuffled.
    */
    void shuffleBallots();

    /**
        @brief Iterate through a given ballots list and assign to respective candidates. Recursively called every round on loser's ballots.

        @param vector<Ballot>: The vector of ballots to iterate through
    */
    void assignBallots(std::vector<Ballot>);

    /**
        @brief Find the loser after every round (the candidate with the lowest vote count) in MAIN candidates list. If there are ties, pick one at random.
    */
    void findLoser();

    int droop;  // Droop quota
    int round;  // The current round of STV finding winners and losers
    int discarded;  // Keeps track of discarded ballots

    // Winners list; sorted from most votes to least votes
    std::vector<Candidate> winners;
    // Losers list; sorted from most votes to least votes
    std::vector<Candidate> losers;
};

#endif  // SRC_DROOP_H_
