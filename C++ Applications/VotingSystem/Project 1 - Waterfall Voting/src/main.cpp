/**
    @file main.cpp

    @copyright Spring 2018, Team 10 CSci 5801
*/

// Includes
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>  // File I/O
#include <sstream>  // String formatting
#include <limits>   // cin error checking
#include <map>      // Dictionary mapping
#include "./ballot.h"
#include "./candidate.h"
#include "./algorithm.h"
#include "./plurality.h"
#include "./droop.h"

// Namespaces
using namespace std;

/**************************************************************************/

// Miscellaneous functions to break up code flow for readability

/**
    @brief Clear cin to ignore the rest of the input. Ensures that only the first input argument is accepted to avoid chaining input to subsequent cin calls.
*/
void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


/**
    @brief Check input file to ensure that it is valid. If not, keep prompting user for valid CSV file. Returns an open filestream.

    @param[in] arg The filename to open
    @param[in] &file Reference to file stream.

    @param[out] &file Reference to open file stream.
*/
void openCSVFile(string arg, ifstream& file) {
    // Keep checking for valid input
    while (true) {
        // Check if CSV file
        if (arg.substr(arg.find_last_of(".") + 1) != "csv") {
            cout << "\nError! \""  << arg << "\" is not a CSV file.";
            cout << "\nPlease input a valid CSV filename: ";

            cin >> arg;
            clearCin();
            continue;
        }

        // Open file
        file.open(arg);
        // Error check for invalid file
        if (!file.is_open()) {
            cout << "\nError! \"" << arg << "\" was unable to be opened."
                << "\nPlease input a valid CSV filename: ";

            cin >> arg;
            clearCin();
        } else {
            break;
        }
    }

    cout << "File \"" << arg << "\" successfully opened.\n";
}


/**
    @brief Splits lines by commas and populates a vector with the resulting substrings.

    @param[in] line The line to split

    @return vector<string>
*/
vector<string> splitLineByCommas(string line) {
    stringstream ssin(line);
    vector<string> s;
    while (ssin.good()) {
        string substr;
        getline(ssin, substr, ',');
        s.push_back(substr);
    }

    return s;
}


/**
    @brief Prompt for the number of seats to fill.

    @param[in] numCandidates The number of running candidates; used for error checking.

    @return int The number of seats being filled.
*/
int promptForSeats(uint numCandidates) {
    int seats;
    cout << "\nInput number of seats to fill: ";
    // Error check, makes sure input is positive and correct
    while (!(cin >> seats) || (seats < 0)) {
        // Clear cin to ignore the rest of the input
        clearCin();
        cout << "Invalid input. Input number of seats to fill: ";
    }
    clearCin();

    // Seats equal to 0
    if (!seats) {
        cout <<
            "\n\nNo seats to fill? Why are you running this then?!"
            << "\nEveryone loses, hooray!\n\n";
        exit(0);
    }

    // Seats greater than candidates
    if (unsigned(seats) > numCandidates) {
        cout << "\nError! More seats than candidates."
            << "\nNow exiting...\n\n";
        exit(1);
    }

    // Seats equal to candidates
    if (unsigned(seats) == numCandidates) {
        cout <<
            "\n\nNumber of seats equal to number of running candidates."
            << "\nEveryone wins, hooray!\n\n";
        exit(0);
    }

    return seats;
}


/**
    @brief Reads the rest of the file to get the ballot information. Creates a vector of new Ballots.

    @param[in] &file Reference to file stream to read from.
    @param[in] candidates The names of the candidates

    @return vector<Ballot> The vector containing ballot information
*/
vector<Ballot> readBallots(ifstream& file, vector<string> candidates) {
    // Make sure file is already open; if not, exit
    if (!file.is_open()) {
        cout << "Error in makeBallots! File stream closed somehow..."
            << "\nNow exiting...\n\n";
        exit(1);
    }

    vector<Ballot> ballots;

    string line;    // Line buffer
    int id = 0;      // Line number used as ballot ID
    while (getline(file, line)) {
        id++;
        vector<string> s = splitLineByCommas(line);

        // Create dictionary mapping to map candidate name to rank
        map<int, string> p_map;

        for (uint i = 0; i < s.size(); i++) {
            // Use atoi to convert to int; returns 0 if blank or pure string
            int pref = atoi(s.at(i).c_str());
            string name = candidates.at(i);

            // Make entry if preference > 0
            if (pref > 0)
                p_map.insert(pair<int, string> (pref, name));
        }

        // Push new Ballot class initialized with id and mapping
        ballots.push_back(Ballot(p_map, id));
    }

    return ballots;
}


/**
    @brief Prompts user for which algorithm to use for finding the winner. Takes in various parameters used to initialize the algorithms' respective constructors.

    @param[in] ballots List of ballots
    @param[in] candidates List of candidate classes
    @param[in] seats The number of seats to be filled

    @return Algorithm* Pointer to object of type Algorithm
*/
Algorithm* chooseAlgorithm(vector<Ballot> ballots,
    vector<Candidate> candidates, int seats) {

    int alg;
    cout
        << "Choose a voting algorithm:\n"
        << "\t1: Plurality\n"
        << "\t2: STV\n"
        << "Anything else: exit program\n"
        << "> ";

    // If anything input besides 1 or 2, exit program
    if (!(cin >> alg) || (alg != 1 && alg != 2)) {
        cout << "\nNow exiting...\n\n";
        exit(0);
    }

    clearCin();

    if (alg == 1) {
        // Plurality algorithm option

        // Clear window
        cout <<
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "\n\nPlurality Results:\n\n";
        return new Plurality(ballots, candidates, seats);

    } else if (alg == 2) {
        // Droop algorithm option

        int opt;
        cout << "\nShuffle ballots?\n"
            << "\t1: Yes\n\t2: No\n> ";

        // If anything input besides 1 or 2, exit program
        while (!(cin >> opt) || (opt != 1 && opt != 2)) {
            cout << "\nInvalid option. Shuffle ballots?"
                << "\n\t1: Yes\n\t2: No\n> ";
            clearCin();
        }

        // Subtract 1 (yes=0, no=1) and invert to set shuffle
        bool shuffle = !(opt - 1);

        // Clear window
        cout <<
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "\n\nSTV (Droop Quota) Results:\n\n";
        return new STV(ballots, candidates, seats, shuffle);

    } else {
        // Catch, just in case
        cout << "\nNow exiting...\n\n";
        exit(0);
    }
}


/**************************************************************************/

/**
    @brief The essential driver to any C/C++ program. Main can take in an optional argument as the filename to open. If this argument is not provided, it will prompt for a valid CSV file. Same if the file provided during either step is invalid.

    It will then prompt for the number of seats to fill, algorithm to use, and other information. As it reads the file, it generates a vector containing the candidate names and a vector containin theballot information from the file. The rest is handles by relevant classes.
*/
int main(int argc, char* argv[]) {
    // Declare the main variables
    vector<Ballot> Ballot_List;
    vector<Candidate> Candidate_List;
    int seats;

    cout <<
        "\nWelcome to the Vote Counter!\n" <<
        "This program reads in a CSV file containing ballot information"
        << " and determines the winner(s) of a specified number of seats."
        << "\n\n\n";

    // Check if file supplied as argument
    string arg;
    if (argc < 2) {
        // No argument supplied, prompt for filename
        cout << "Please input a CSV filename: ";
        cin >> arg;
        clearCin();
        cout << endl;
    } else {
        arg = argv[1];
    }

    // Check for valid CSV file
    ifstream file;  // File stream
    openCSVFile(arg, file);

    // Make sure filestream is open; if not, exit
    if (!file.is_open()) {
        cout << "Error in Main! File stream closed somehow..."
            << "\nNow exiting...\n\n";
        exit(1);
    }

    // Read first line to get candidate names
    string line;  // Line buffer
    getline(file, line);
    vector<string> candidateNames = splitLineByCommas(line);
    // Create vector of candidate classes
    for (uint i = 0; i < candidateNames.size(); i++) {
        Candidate_List.push_back(Candidate(candidateNames.at(i)));
    }

    // Get number of seats to fill
    // Pass in number of candidates for error checking
    seats = promptForSeats(Candidate_List.size());

    // Read rest of ballots
    // Pass in candidate names to initialize dictionary
    Ballot_List = readBallots(file, candidateNames);

    // Get a pointer to the type of algorithm to run (polymorphism)
    Algorithm* alg = chooseAlgorithm(Ballot_List, Candidate_List, seats);

    alg->run();             // Run algorithm
    alg->printResults();    // Print results to terminal
    alg->generateReport();  // Generate report file
    delete alg;             // Reallocate heap

    // Close filestream if still open
    if (file.is_open())
        file.close();

    return 0;
}
