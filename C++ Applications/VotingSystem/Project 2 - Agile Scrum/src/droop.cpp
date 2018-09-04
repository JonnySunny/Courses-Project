/**
    @file droop.cpp

    @copyright Spring 2018, Team 10 CSci 5801
*/

// Includes
#include <iostream>     // For cin/cout
#include <algorithm>    // For random_shuffle and sort
#include <map>          // For dictionary mapping
#include "./droop.h"
#include "./ballot.h"
#include "./candidate.h"

// Namespaces
using std::string;
using std::stringstream;
using std::vector;
using std::cout;
using std::endl;
using std::map;

/**************************************************************************/

// Constructor
STV::STV(vector<Ballot> ballots, vector<Candidate> candidates,
    int seats, bool shuffle) :
        Algorithm(ballots, candidates, seats),
        round(0),
        discarded(0) {
            // Calculate droop quota: floor(ballots/(seats+1))+1
            // int division automatically floors
            droop = ballots.size() / (seats + 1) + 1;

            if (shuffle)
                shuffleBallots();

            // Report headers; various information pertaining to election
            report << dateTime()
                  << "\n\nSTV algorithm\n\nCandidate names:";

            for (uint i = 0; i < candidates.size(); i++)
                report << "\n\t" << candidates.at(i).get_name();

            report << "\nNumber of seats to fill: " << seats
                << "\nBallot shuffling: " << shuffle
                << "\nNumber of ballots: " << ballots.size()
                << "\nDroop quota: " << droop
                << "\n\n";

            // Headers must be added to all other reports (convert to string)
            short_report << report.str();
        }

// Deconstructor
STV::~STV() {
    winners.clear();
    losers.clear();
}



/**************************************************************************/


void STV::run() {
    // Call with main ballots list
    assignBallots(ballot_list);

    // Add winners and losers to report
    report << "\n\nWinners (met droop):";
    for (uint i = 0; i < winners.size(); i++) {
        report << "\n\t" << winners.at(i).get_name()
            << " (" << winners.at(i).voteCounts()
            << " votes)";
    }

    report << "\n\nLosers (did not meet droop):";
    for (uint i = 0; i < losers.size(); i++) {
        report << "\n\t" << losers.at(i).get_name()
            << " (" << losers.at(i).voteCounts()
            << " votes)";
    }

    // Add # of discarded votes to report too
    report << "\n\n" << discarded
        << " ballots discarded for not having enough candidates ranked";
}


void STV::printResults() {
    // Temporary string stream buffer
    stringstream results;

    // First iterate over winner vector, pop front off every iteration
    for (uint i = 0; i < (unsigned)get_Seats(); i++) {
        // If winners vector is exhausted, start pulling from losers list
        // Make sure losers list isn't empty as well! (Sanity check)
        if (winners.empty() && losers.size()) {
            results << "Winner of Seat " << (i+1) << ": "
                << losers.front().get_name()
                << " (" << losers.front().voteCounts()
                << " votes; did not meet droop)\n\n";

            // Erase front
            losers.erase(losers.begin());

        } else {
            results << "Winner of Seat " << (i+1) << ": "
                << winners.front().get_name()
                << " (" << winners.front().voteCounts() << " votes)\n\n";

            // Erase front
            winners.erase(winners.begin());
        }
    }  // End for loop

    // Print buffer to both terminal and short report
    cout << results.str();
    // Add # of discarded votes to report too
    short_report << results.str() << endl << discarded
        << " ballots discarded for not having enough candidates ranked";
}


// Search for where in the candidates_list vector a candidate is located
const int STV::findCandidateIndexByName(string name) {
    for (uint i = 0; i < candidates_list.size(); i++) {
        if (name == candidates_list.at(i).get_name())
            return i;
    }

    // Not found, return -1
    return -1;
}


void STV::addWinner(Candidate c) {
    // Ensure that the winner has reached the droop quota
    if (c.voteCounts() >= droop)
        // Winners added in order; add new winner to back
        winners.push_back(c);
}


void STV::addLoser(Candidate c) {
    // Losers added backwards; last loser is first in list
    // This ensures that the best of the losers win if needed
    losers.insert(losers.begin(), c);
}


/**************************************************************************/

// Private methods below

// Finds the candidate with the least votes, adds them to losers list
void STV::findLoser() {
    // If main list empty, exit
    if (candidates_list.empty())
        return;

    // Create closure to take in two Candidates and sort
    auto dec = [](Candidate& c1, Candidate& c2) {
        return c1.voteCounts() > c2.voteCounts();
    };

    // Sort candidate list by decreasing number of votes
    sort(candidates_list.begin(), candidates_list.end(), dec);

    // Add last member to losers list
    addLoser(candidates_list.back());
    // Remove from main list
    candidates_list.pop_back();
}


// Randomly shuffleballots (private method)
void STV::shuffleBallots() {
    // Seed RNG
    srand(time(NULL));

    // Create RNG closure (C++11 lambda functions)
    auto rng = [](int i) {return random()%i;};

    // Call random_shuffle on ballots vector with rng function
    random_shuffle(ballot_list.begin(), ballot_list.end(), rng);
}


// Recursive function; will recursively call self on loser's ballots
void STV::assignBallots(vector<Ballot> ballots) {
    // Termination condition:
    // Main candidates vector is empty, meaning all are either winners or losers
    if (candidates_list.empty())
        return;

    // Increment round
    round++;

    report << "\nRound " << round << ":\n\t"
        << winners.size() << " winners\n\t"
        << losers.size() << " losers\n";

    // Iterate through ballots list and assign to candidates
    for (uint i = 0; i < ballots.size(); i++) {
        // Get preference map
        map<int, string> p_map = ballots.at(i).get_preference_map();

        // If less than half of candidates are ranked, discard (continue)
        if (p_map.size() < candidates_list.size()/2.) {
            report << "\n\tBallot ID " << ballots.at(i).get_id()
                << " discarded (" << p_map.size()
                << "/" << candidates_list.size()
                << " candidates ranked)";

            discarded++;
            continue;
        }

        // Loop through keys
        // C++ 14 guarantees it iterates through from least to greatest
        for (const auto &pair : p_map) {
            // Get candidate name
            string name = pair.second;

            // Find if the candidate is still in the running
            // Assign to first candidate found
            int index = findCandidateIndexByName(name);

            // If so, that's the most preferred candidate
            // Assign ballot to them and break out of loop
            if (index != -1) {
                // Pointer to candidate
                Candidate* c = &candidates_list.at(index);
                c->addBallot(ballots.at(i));

                report << "\n\tBallot ID " << ballots.at(i).get_id()
                    << " assigned to " << name
                    << " (" << c->voteCounts() << " votes)";

                // Check to see if candidate has reached droop
                // If so, remove them from the main vector
                // Add to winners list
                if (c->voteCounts() >= droop) {
                    addWinner(*c);
                    candidates_list.erase(candidates_list.begin() + index);

                    report << "\n\t\t" << name << " has reached droop quota"
                        << "\n\t\tMoving to winners list";
                }

                break;
            }  // End index test
        }  // End key iteration loop
    }  // End ballot loop


    // Check again to make sure main list isn't empty
    if (candidates_list.empty())
        return;

    /*
        After all ballots have been processed, find the loser and process their ballots.
        There is always a loser, which is always added to the front of the losers list.
        Recursively call using that candidates assigned ballots.
    */
    findLoser();
    // Pointer to loser
    Candidate* loser = &losers.front();

    report << "\n\n\t" << loser->get_name() << " moved to losers list with "
        << loser->voteCounts() << " votes\n\t"
        << loser->get_ballots().size()
        << " ballots will be redistributed\n";
    assignBallots(loser->get_ballots());
}
