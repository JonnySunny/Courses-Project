/**
 * @file plurality.cc
 *
 * @copyright 2018 5801 Team 10, All rights reserved.
 */

// Includes
#include <algorithm>    // For sort
#include <iostream>     // For cin/cout
#include <map>          // For dictionary mapping
#include "./plurality.h"
#include "./ballot.h"
#include "./candidate.h"

// Namespaces
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;
using std::map;

/**************************************************************************/

Plurality::Plurality(vector<Ballot> b, vector<Candidate> c, int seats) :
    Algorithm(b, c, seats),
    skipped(0) {
        // Report headers; various information pertaining to election
        report << dateTime()
            << "\n\nPlurality algorithm\n\nCandidate names:";

        for (uint i = 0; i < c.size(); i++)
            report << "\n\t" << c.at(i).get_name();

        report << "\nNumber of seats to fill: " << seats
            << "\nNumber of ballots: " << b.size()
            << "\n\n";

        // Headers must be added to all other reports (convert to string)
        short_report << report.str();
    }


void Plurality::run() {
    // Iterate through every ballot
    for (uint i = 0; i < ballot_list.size(); i++) {
        // Get preference map and pick first entry
        // C++14 guarantees keys are sorted from least to greatest
        map<int, string> p_map = ballot_list.at(i).get_preference_map();

        // Empty ballot; log in report and skip
        if (p_map.size() <= 0) {
            report << "\nBallot ID " << ballot_list.at(i).get_id()
                << " empty; skipping...";

            skipped++;
            continue;
        }

        // Candidate name from first key
        string name = p_map.begin()->second;

        // Find candidate name
        for (uint j = 0; j < candidates_list.size(); j++) {
            // If name found, add current ballot to that candidate
            // If not, the ballot is simply skipped
            if (candidates_list.at(j).get_name() == name) {
                candidates_list.at(j).addBallot(ballot_list.at(i));

                report << "\nBallot ID " << ballot_list.at(i).get_id()
                    << " assigned to " << name << " ("
                    << candidates_list.at(j).voteCounts()
                    << " votes)";
            }  // End name test
        }  // End candidate loop
    }  // End ballot loop

    // Sort
    sortCandidates();

    // Add winners and losers to report
    report << "\n\nWinners:";
    for (uint k = 0;
    k < (unsigned)get_Seats() && k < candidates_list.size();
    k++) {
        report << "\n\t" << candidates_list.at(k).get_name()
            << " (" << candidates_list.at(k).voteCounts()
            << " votes)";
    }

    report << "\n\nLosers:";
    for (uint k = (unsigned)get_Seats();
    k < candidates_list.size();
    k++) {
        report << "\n\t" << candidates_list.at(k).get_name()
            << " (" << candidates_list.at(k).voteCounts()
            << " votes)";
    }

    // Add # of skipped votes to report too
    report << "\n\n" << skipped << " empty ballots discarded";
}


void Plurality::printResults() {
    // Temporary string stream buffer
    stringstream results;

    // Pull enough candidates from sorted list to fill seats
    for (uint i = 0;
    i < (unsigned)get_Seats();
    i++) {
        // Sanity check; make sure there are still candidates
        if (i > candidates_list.size()) {
            cout << "\nError! More seats than candidates.\nNow exiting...";
            exit(1);
        }

        results << "Winner of Seat " << (i+1) << ": "
            << candidates_list.at(i).get_name()
            << " (" << candidates_list.at(i).voteCounts()
            << " votes)\n\n";
    }

    // Print buffer to both terminal and short report
    cout << results.str();
    // Add # of skipped votes to report too
    short_report << results.str() << endl << skipped
        << " empty ballots discarded";
}


/**************************************************************************/

// Private methods below

// Sort candidates by decreasing vote count
void Plurality::sortCandidates() {
    // Sanity check; make sure list isn't empty
    if (candidates_list.empty())
        return;

    // Create closure to take in two Candidates and sort
    srand(time(NULL));  // Seed RNG
    auto dec = [](Candidate& c1, Candidate& c2) {
        // If equal, return true or false randomly
        if (c1.voteCounts() == c2.voteCounts())
            return static_cast<bool>(random()%2);

        return c1.voteCounts() > c2.voteCounts();
    };

    // Sort candidate list by decreasing number of votes
    sort(candidates_list.begin(), candidates_list.end(), dec);
}
