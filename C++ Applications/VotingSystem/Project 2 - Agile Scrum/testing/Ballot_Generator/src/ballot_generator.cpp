/**
    @file ballot_generator.cpp

    @copyright 2018, Raheel Qureshi
*/

// Includes
#include <iostream>
#include <string>
#include <vector>
#include <fstream>      // File I/O
#include <sstream>      // stringstream
#include <limits>       // cin error checking
#include <algorithm>    // random_shuffle

using namespace std;

/**************************************************************************/

// Test candidate names (52 in total)
const string namePool = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/**************************************************************************/

/*
    Clear cin to ignore the rest of the input. Ensures that only the first input argument is accepted to avoid chaining input to subsequent cin calls.
*/
void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


/*
    Makes a comma delineated line
    Takes in the number of cells columns to make
*/
string makeLine(int cols) {
    // String stream; added to format and returned as final string
    stringstream ret;
    // Vector to hold strings; either number or empty string
    vector<string> rankings;
    // Number of actual ranks to fill out; random (0 - cols)
    int ranks = random() % (cols+1);

    // Fill out the columns with the ranks (1 to ranks)
    // If the iterator has passed the rank cutoff, then use an empty string
    for (int i = 0; i < cols; i++) {
        string j = i < ranks ? to_string(i+1) : "";
        rankings.push_back(j);
    }

    // Randomly shuffle the vector
    auto rng = [](int a) {return random() % a;};
    random_shuffle(rankings.begin(), rankings.end(), rng);

    // Feed into stringstream as comma delineated line
    // Add commas after each entry except for the last one (end line)
    for (uint i = 0; i < rankings.size(); i++) {
        ret << rankings.at(i) << (i < rankings.size()-1 ? "," : "");
    }

    // Turn into string and return
    return ret.str();
}


int main() {
    // Seed RNG
    srand(time(NULL));

    //////////////////////////////////////////////////////////

    // Prompt for seats
    uint seats;
    cout << "\nNumber of seats to fill: ";
    while (!(cin >> seats)) {
        clearCin();
        cout << "\nInvalid. Number of seats to fill: ";
    }
    clearCin();
    // Cutoff at name pool size
    if (seats >= namePool.length()) {
        cout << "Too large, cutting down\n";
        seats = namePool.length();
    }

    cout << seats << endl;

    //////////////////////////////////////////////////////////

    // Prompt for number of candidates
    uint num;
    cout << "\nNumber of test candidates (must be >= # of seats): ";
    while (!(cin >> num)) {
        clearCin();
        cout << "\nInvalid. Number of test candidates: ";
    }
    clearCin();
    // If less than number of seats, raise to number of seats + 1
    if (num < seats) {
        cout << "Candidates cannot be less than seats, raising number by 1 more than seats\n";
        num = seats + 1;
    }
    // Cutoff at size of name pool
    if (num > namePool.length()) {
        cout << "Too large, cutting down\n";
        num = namePool.length();
    }

    // Convert into comma delineated line
    stringstream line;
    for (uint i = 0; i < num; i++)
        line << '[' << namePool.at(i) << ']' << (i < num-1 ? "," : "");
    // Convert to string
    string candidates = line.str();

    cout << num << endl;

    //////////////////////////////////////////////////////////

    // Prompt for algorithm (either p or s)
    char alg;
    cout << "\nAlgorithm (p)lurality or (s)tv: ";
    while (true) {
        // Input check
        if (!(cin >> alg)) {
            clearCin();
            cout << "\nInvalid. Algorithm: ";
            continue;
        }
        clearCin();

        // "p" or "s"
        if (tolower(alg) != 'p' && toupper(alg) != 'S') {
            cout << "\nInvalid. Algorithm: ";
            continue;
        }

        break;
    }

    //////////////////////////////////////////////////////////

    // Prompt for ballots
    uint ballots;
    cout << "\nNumber of ballots to make (max 100,000): ";
    while (!(cin >> ballots)) {
        clearCin();
        cout << "\nInvalid. Number of ballots to make: ";
    }
    clearCin();
    // Cutoff at 100,000
    if (ballots > 100000) {
        cout << "Too large, cutting down\n";
        ballots = 100000;
    }

    cout << ballots << endl;

    //////////////////////////////////////////////////////////

    // Open file
    ofstream out;
    out.open("Ballot.csv");

    // Put preliminary stuff
    out << alg << endl << seats << endl << candidates;

    // Print out each randomized ballot (pass in number of candidates)
    for (uint i = 0; i < ballots; i++)
        out << endl << makeLine(num);

    out.close();

    cout << "\n\nDone processing\n\n";
    return 0;
}
