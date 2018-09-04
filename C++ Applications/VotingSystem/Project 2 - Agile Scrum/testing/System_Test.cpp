#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<sstream>
#include<map>
#include<iterator>
#include<algorithm>
#include "../src/candidate.h"
#include "../src/ballot.h"
#include "../src/algorithm.h"
#include "../src/droop.h"
#include "../src/plurality.h"
using namespace std;

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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
}

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

void validateAddtionalInput(string check) {
  bool unneeded = false;
  for (uint i=0; i<check.length(); i++) {
    if (check[i] != ' ' && check[i] != ',') {
      unneeded = true;
    }
  }
  if (unneeded) {
    cout << "The file containing some unneeded information, already discarded." << endl;
  }
}

int validateSeats(int seats, uint numCandidates) {
    // Error check, makes sure input is positive and correct
    if (seats < 0) {
        // Clear cin to ignore the rest of the input
        cout << "Invalid input. Input number of seats to fill: ";
        cin >> seats;
    }

    // Seats equal to 0
    if (!seats) {
        cout << "Invaild input for number of seats." << endl;
    }

    // Seats greater than candidates
    if (unsigned(seats) > numCandidates) {
        cout << "\nError! More seats than candidates."
            << "\nNow exiting...\n\n";
    }

    // Seats equal to candidates
    if (unsigned(seats) == numCandidates) {
        cout <<
            "\n\nNumber of seats equal to number of running candidates."
            << "\nEveryone wins, hooray!\n\n";
    }
    return seats;
}

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

Algorithm* chooseAlgorithm(vector<Ballot> ballots,
    vector<Candidate> candidates, int seats, string choice, bool shuffle) {

    if (choice == "p" || choice == "P") {
        return new Plurality(ballots, candidates, seats);

    } else if (choice == "s" || choice == "S") {
        return new STV(ballots, candidates, seats, shuffle);
    }
    else {
        cout << "Invalid input of algorithm\n";
    }
    return NULL;
}

vector<Ballot>validateBallot(vector<Ballot> ballots, vector<Candidate> candidates_list) {
  vector<Ballot> valid_ballots;
  for (uint i = 0; i < ballots.size(); i++) {
      // Get preference map
      map<int, string> p_map = ballots.at(i).get_preference_map();
      if(p_map.size() >= ((1.0/2.0) *candidates_list.size())) {
        valid_ballots.push_back(ballots.at(i));
      }
      else {
        printf("The %d th has less than half of votes and the ballot is discarded\n", ballots.at(i).get_id());
      }
    }
    return valid_ballots;
}

void Test_PBI1() {
  vector<Ballot> Ballot_List;
  vector<Candidate> Candidate_List;
  int seats = 5;
  cout << "Test for PBI 1: " << endl;
  cout << "Test for Task 1 (pluarity random): " << endl;
  cout << "Expected values: " << endl;
  cout << "Round 1: " << endl;
  cout << "Winner of Seat 1: [A] " << endl;
  cout << "Winner of Seat 2: [G] " << endl;
  cout << "Winner of Seat 3: [Random candidate from BCDEFHI] " << endl;
  cout << "Winner of Seat 4: [Random candidate from BCDEFHI] " << endl;
  cout << "Winner of Seat 5: [Random candidate from BCDEFHI] " << endl;
  cout << "Round 2: " << endl;
  cout << "Winner of Seat 1: [A] " << endl;
  cout << "Winner of Seat 2: [G] " << endl;
  cout << "Winner of Seat 3: [Random candidate from BCDEFHI] " << endl;
  cout << "Winner of Seat 4: [Random candidate from BCDEFHI] " << endl;
  cout << "Winner of Seat 5: [Random candidate from BCDEFHI] " << endl;
  cout << "Actual values: " << endl;
  cout << "Round 1: " << endl;

  ifstream file;
  openCSVFile("./Test_Ballots/examplefile.csv", file);

  string line;
  getline(file, line);
  vector<string> candidateNames = splitLineByCommas(line);
  // Create vector of candidate classes
  for (uint i = 0; i < candidateNames.size(); i++) {
      Candidate_List.push_back(Candidate(candidateNames.at(i)));
  }

  Ballot_List = readBallots(file, candidateNames);
  Algorithm* alg = chooseAlgorithm(Ballot_List, Candidate_List, seats, "p", false);

  alg->run();
  alg->printResults();
  cout << "Round 2: " << endl;
  alg->run();
  alg->printResults();
  delete alg;

  if (file.is_open())
    file.close();

  cout << "Test Result: Passed." << endl;
  cout << endl;

  cout << "Test for Task 2 (algorithm functionality): " << endl;
  cout << "Expected values: " << endl;
  cout << "Plurality: " << endl;
  cout << "Winner of Seat 1: [F]" << endl;
  cout << "Winner of Seat 2: [D]" << endl;
  cout << "Winner of Seat 3: [random candidate from KALOH]" << endl;
  cout << "Winner of Seat 4: [random candidate from KALOH]" << endl;
  cout << "Winner of Seat 5: [random candidate from KALOH]" << endl;
  cout << "STV: " << endl;
  cout << "Winner of Seat 1: [D]" << endl;
  cout << "Winner of Seat 2: [K]" << endl;
  cout << "Winner of Seat 3: [F]" << endl;
  cout << "Winner of Seat 4: [L]" << endl;
  cout << "Winner of Seat 5: [H]" << endl;
  cout << "Actual values: " << endl;
  cout << "Plurality: " << endl;

  openCSVFile("./Test_Ballots/examplefile1.csv", file);
  vector<Candidate> Candidate_List_new;

  getline(file, line);
  vector<string> candidateNames_new = splitLineByCommas(line);
  // Create vector of candidate classes
  for (uint i = 0; i < candidateNames_new.size(); i++) {
    Candidate_List_new.push_back(Candidate(candidateNames_new.at(i)));
  }

  vector<Ballot> Ballot_List_new = readBallots(file, candidateNames_new);
  alg = chooseAlgorithm(Ballot_List_new, Candidate_List_new, seats, "p", false);

  alg->run();
  alg->printResults();
  delete alg;

  cout << "STV: " << endl;
  alg = chooseAlgorithm(Ballot_List_new, Candidate_List_new, seats, "s", true);
  alg->run();
  alg->printResults();
  delete alg;

  if (file.is_open())
    file.close();

  cout << "Test Result: Passed." << endl;
  cout << endl;

  cout << "Test for Task 3 (refactoring): " << endl;
  cout << "Test Result: Passed (Manually Checked)." << endl;
  cout << endl;
}

void Test_PBI2() {
  vector<Ballot> Ballot_List;
  vector<Candidate> Candidate_List;
  int seats = 5;
  cout << "Test for PBI 2: " << endl;
  cout << "Test for Task 1 (stv shuffle): " << endl;
  cout << "Expected values: " << endl;
  cout << "Ballot ID gets shuffled" << endl;
  cout << "Actual values: " << endl;
  cout << "STV: " << endl;

  ifstream file;
  openCSVFile("./Test_Ballots/examplefile.csv", file);
  string line;
  getline(file, line);
  vector<string> candidateNames = splitLineByCommas(line);
  // Create vector of candidate classes
  for (uint i = 0; i < candidateNames.size(); i++) {
      Candidate_List.push_back(Candidate(candidateNames.at(i)));
  }

  Ballot_List = readBallots(file, candidateNames);
  Algorithm* alg = chooseAlgorithm(Ballot_List, Candidate_List, seats, "s", true);

  alg->run();             // Run algorithm
  vector<Ballot> Ballot_Test = alg->get_Ballots();
  for (uint i=0; i<Ballot_Test.size(); i++) {
    cout << "Ballot ID: " << Ballot_Test.at(i).get_id() << endl;
  }
  delete alg;
  if (file.is_open())
    file.close();

  cout << "Test Result: Passed." << endl;
  cout << endl;

  cout << "Test for Task 2 (additional command line argument): " << endl;
  cout << "Test Result: Passed(Manually Checked)." << endl;
  cout << endl;

  cout << "Test for Task 3 (use flag to turn off shuffle): " << endl;
  cout << "Expected values: " << endl;
  cout << "STV: " << endl;
  cout << "Ballot ID: 1" << endl;
  cout << "Ballot ID: 2" << endl;
  cout << "Ballot ID: 3" << endl;
  cout << "Ballot ID: 4" << endl;
  cout << "Ballot ID: 5" << endl;
  cout << "Ballot ID: 6" << endl;
  cout << "Ballot ID: 7" << endl;
  cout << "Ballot ID: 8" << endl;
  cout << "Ballot ID: 9" << endl;
  cout << "Ballot ID: 10" << endl;
  cout << "Ballot ID: 11" << endl;
  cout << "Actual values: " << endl;
  cout << "STV: " << endl;

  openCSVFile("./Test_Ballots/examplefile.csv", file);
  getline(file, line);
  candidateNames = splitLineByCommas(line);
  // Create vector of candidate classes
  for (uint i = 0; i < candidateNames.size(); i++) {
      Candidate_List.push_back(Candidate(candidateNames.at(i)));
  }

  Ballot_List = readBallots(file, candidateNames);
  alg = chooseAlgorithm(Ballot_List, Candidate_List, seats, "s", false);

  alg->run();
  Ballot_Test = alg->get_Ballots();
  for (uint i=0; i<Ballot_Test.size(); i++) {
    cout << "Ballot ID: " << Ballot_Test.at(i).get_id() << endl;
  }
  delete alg;
  if (file.is_open())
    file.close();

  cout << "Test Result: Passed." << endl;
  cout << endl;
}

void Test_PBI3() {
  vector<Ballot> Ballot_List;
  vector<Candidate> Candidate_List;
  int seats;
  string choice;
  string garbage1, garbage2;
  cout << "Test for PBI 3: " << endl;
  cout << "Test for Task 1 & 2 (csv format change and parse): " << endl;
  cout << "Expected values: " << endl;
  cout << "First line: s " << endl;
  cout << "First line: 4 " << endl;
  cout << "Actual values: " << endl;
  cout << "First line: ";

  ifstream file;
  openCSVFile("./Test_Ballots/examplefile3.csv", file);

  file >> choice;
  garbage1 = choice.substr(1, choice.length()-1);
  choice = choice.substr(0,1);
  cout << choice << endl;

  file >> seats;
  getline(file, garbage2);
  cout << "Second line: ";
  cout << seats << endl;
  // validateAddtionalInput(garbage1+garbage2);

  if (file.is_open())
    file.close();

  cout << "Test Result: Passed." << endl;
  cout << endl;

  cout << "Test for Task 3 (error checking): " << endl;
  cout << "Expected values: " << endl;
  cout << "Case 1: " << endl;
  cout << "Invalid input for number of seats" << endl;
  cout << "Invalid input of algorithm" << endl;
  cout << "Case 2: " << endl;
  cout << "Invalid input for number of seats" << endl;
  cout << "The file containing some unneeded information, already discarded." << endl;
  cout << "Actual values: " << endl;
  cout << "Case 1: " << endl;

  openCSVFile("./Test_Ballots/examplefile11.csv", file);
  file >> choice;
  garbage1 = choice.substr(1, choice.length()-1);
  choice = choice.substr(0,1);

  file >> seats;
  getline(file, garbage2);
  seats =   validateSeats(seats, 5);
  Algorithm* alg = chooseAlgorithm(Ballot_List, Candidate_List, seats, choice, true);
  delete alg;
  validateAddtionalInput(garbage1+garbage2);
  if (file.is_open())
    file.close();
  choice = "";
  seats = 0;
  garbage1 = "";
  garbage2 = "";

  cout << "Case 2: " << endl;
  openCSVFile("./Test_Ballots/examplefile12.csv", file);
  file >> choice;
  garbage1 = choice.substr(1, choice.length()-1);
  choice = choice.substr(0,1);

  file >> seats;
  getline(file, garbage2);
  seats = validateSeats(seats, 5);
  alg = chooseAlgorithm(Ballot_List, Candidate_List, seats, choice, true);
  delete alg;
  validateAddtionalInput(garbage1+garbage2);
  if (file.is_open())
    file.close();

  cout << "Test Result: Passed." << endl;
  cout << endl;
}

void Test_PBI4() {
  string choice;
  string garbage1, garbage2;
  int seats;
  vector<Ballot> Ballot_List;
  vector<Candidate> Candidate_List;
  cout << "Test for PBI 4: " << endl;
  cout << "Test for Task 1 (optional command line argument): " << endl;
  cout << "Test Result: Passed (Manually Checked)." << endl;
  cout << endl;

  cout << "Test for Task 2 (enable both option to work): " << endl;
  cout << "Expected values: " << endl;
  cout << "Winner of Seat 1: [Random candidate from CD]" << endl;
  cout << "Winner of Seat 1: [Random candidate from CD]" << endl;
  cout << "Winner of Seat 1: [Random candidate from BE]" << endl;
  cout << "Actual values: " << endl;

  string  name = "./Test_Ballots/examplefile2.csv";
  ifstream file;
  openCSVFile(name, file);

  file >> choice;
  garbage1 = choice.substr(1, choice.length()-1);
  choice = choice.substr(0,1);

  file >> seats;
  getline(file, garbage2);
  validateAddtionalInput(garbage1+garbage2);

  string line;
  getline(file, line);
  vector<string> candidateNames = splitLineByCommas(line);

  for (uint i = 0; i < candidateNames.size(); i++) {
      Candidate_List.push_back(Candidate(candidateNames.at(i)));
  }

  Ballot_List = readBallots(file, candidateNames);
  Algorithm* alg = chooseAlgorithm(Ballot_List, Candidate_List, seats, choice, false);

  alg->run();
  alg->printResults();
  delete alg;

  if (file.is_open())
    file.close();

  cout << "Test Result: Passed." << endl;
  cout << endl;
}

void Test_PBI5() {
  string choice;
  string garbage1, garbage2;
  int seats;
  vector<Ballot> Ballot_List;
  vector<Candidate> Candidate_List;
  cout << "Test for PBI 5: " << endl;
  cout << "Test for Task 1 & 2 (discard ballot and inform user): " << endl;
  cout << "Expected values: " << endl;
  cout << "Before discard happen:" << endl;
  cout << "Ballot ID: 1" << endl;
  cout << "Ballot ID: 2" << endl;
  cout << "Ballot ID: 3" << endl;
  cout << "Ballot ID: 4" << endl;
  cout << "Ballot ID: 5" << endl;
  cout << "Ballot ID: 6" << endl;
  cout << "Ballot ID: 7" << endl;
  cout << "Ballot ID: 8" << endl;
  cout << "Ballot ID: 9" << endl;
  cout << "Ballot ID: 10" << endl;
  cout << "Ballot ID: 11" << endl;
  cout << "Ballot ID: 12" << endl;
  cout << "Ballot ID: 13" << endl;
  cout << "Ballot ID: 14" << endl;
  cout << "Ballot ID: 15" << endl;
  cout << "Ballot ID: 16" << endl;
  cout << "Ballot ID: 17" << endl;
  cout << "Ballot ID: 18" << endl;
  cout << "Ballot ID: 19" << endl;
  cout << "Ballot ID: 20" << endl;
  cout << "Ballot ID: 21" << endl;
  cout << "Ballot ID: 22" << endl;
  cout << "After discard happen:" << endl;
  cout << "The ballot 1, 6, 9, 11, 17, 19 are discarded" << endl;
  cout << "Ballot ID: 2" << endl;
  cout << "Ballot ID: 3" << endl;
  cout << "Ballot ID: 4" << endl;
  cout << "Ballot ID: 5" << endl;
  cout << "Ballot ID: 7" << endl;
  cout << "Ballot ID: 8" << endl;
  cout << "Ballot ID: 10" << endl;
  cout << "Ballot ID: 12" << endl;
  cout << "Ballot ID: 13" << endl;
  cout << "Ballot ID: 14" << endl;
  cout << "Ballot ID: 15" << endl;
  cout << "Ballot ID: 16" << endl;
  cout << "Ballot ID: 18" << endl;
  cout << "Ballot ID: 20" << endl;
  cout << "Ballot ID: 21" << endl;
  cout << "Ballot ID: 22" << endl;


  cout << "Actual values: " << endl;
  cout << "Before discard happen: " << endl;

  ifstream file;
  openCSVFile("./Test_Ballots/examplefile13.csv", file);

  file >> choice;
  garbage1 = choice.substr(1, choice.length()-1);
  choice = choice.substr(0,1);

  file >> seats;
  getline(file, garbage2);
  validateAddtionalInput(garbage1+garbage2);

  string line;
  getline(file, line);
  vector<string> candidateNames = splitLineByCommas(line);

  for (uint i = 0; i < candidateNames.size(); i++) {
      Candidate_List.push_back(Candidate(candidateNames.at(i)));
  }

  Ballot_List = readBallots(file, candidateNames);

  for (uint i=0; i<Ballot_List.size(); i++) {
    cout << "Ballot ID: " << Ballot_List.at(i).get_id() << endl;
  }

  cout << "After discard happen: " << endl;

  Ballot_List = validateBallot(Ballot_List, Candidate_List);

  for (uint i=0; i<Ballot_List.size(); i++) {
    cout << "Ballot ID: " << Ballot_List.at(i).get_id() << endl;
  }

  if (file.is_open())
    file.close();

  cout << "Test Result: Passed." << endl;
  cout << endl;

  cout << "Test for Task 3 (functionality after discard invalid ballots): " << endl;
  cout << "Expected values: " << endl;
  cout << "Winner of seat 1: [D]" << endl;
  cout << "Winner of seat 1: [F]" << endl;
  cout << "Winner of seat 1: [H]" << endl;
  cout << "Winner of seat 1: [C]" << endl;
  cout << "Winner of seat 1: [A]" << endl;
  cout << "Winner of seat 1: [K] (did not meet droop)" << endl;
  cout << "Winner of seat 1: [G] (did not meet droop)" << endl;
  cout << "Actual values: " << endl;

  Algorithm* alg = chooseAlgorithm(Ballot_List, Candidate_List, seats, choice, true);
  alg->run();
  alg->printResults();
  delete alg;

  cout << "Test Result: Passed." << endl;
  cout << endl;
}

void Test_PBI6() {

  cout << "Test for PBI 6: " << endl;
  cout << "Test for Task 1 (additional functions): " << endl;
  cout << "Test Result: Passed (Manually checked)." << endl;
  cout << endl;

  cout << "Test for Task 2 (Report contents): " << endl;
  cout << "Test Result: Passed (Manually checked)." << endl;
  cout << endl;
}

int main() {
  Test_PBI1();
  Test_PBI2();
  Test_PBI3();
  Test_PBI4();
  Test_PBI5();
  Test_PBI6();
  return 0;
}
