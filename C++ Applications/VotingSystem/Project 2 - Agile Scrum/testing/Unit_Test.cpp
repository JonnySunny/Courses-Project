/**
 * @file Unit_Test.cpp
 *
 * @brief This file simulates something akin to the GTest framework and tests all public methods of the classes used in the main program.
 */

// Includes
#include "../src/ballot.h"
#include "../src/candidate.h"
#include "../src/droop.h"
#include "../src/plurality.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

/**************************************************************************/

// Global variables

// Keep track of total amount of tests and tests passed
int TCOUNT = 0, TPASS = 0;

// Print out a line clear
void lineClear() {
    cout << "\n==========================================\n";
}


/*
    Template class functions, used as a general testing interface

    ASSERT exits on fail (indicates an important test that must be passed)

    TEST informs if the test has failed, yet continues on (used for tests that can still continue if not broken)

    Takes in a type T to test, a type T to compare, a string for the name of what's being testing, and a local test count and test pass

    Pass in what is expected first, and then what's being tested (the result of the function call)
*/
template <class T>
void ASSERT(T expectedVal, T testVal, string testName, int &testCount, int &testPass) {
    // Increment global test count and test count for local call
    TCOUNT++;
    testCount++;

    lineClear();

    cout << "Testing of " << testName << ":\nExpected "
        << expectedVal << ", got " << testVal;

    if (testVal == expectedVal) {
        // Passed; increment total and local test passes
        TPASS++;
        testPass++;

    } else {
        cout << "\n\nTest failed! Exiting...\n\n";
        exit(1);
    }
}

template <class T>
void TEST(T expectedVal, T testVal, string testName, int &testCount, int &testPass) {
    // Increment global test count and test count for local call
    TCOUNT++;
    testCount++;

    lineClear();

    cout << "Testing of " << testName << ":\nExpected "
        << expectedVal << ", got " << testVal;

    if (testVal == expectedVal) {
        // Passed; increment total and local test passes
        TPASS++;
        testPass++;

    } else {
        cout << "\n\nTest failed!";
    }
}

/**************************************************************************/

// Overloaded operators used for testing

// Vector
template <class T>
ostream& operator<<(ostream& stream, const vector<T>& vec) {
    stream << "Vector";
    return stream;
}

// Map
template <class K, class T>
ostream& operator<<(ostream& stream, const map<K, T>& map) {
    stream << "Key/Value Map";
    return stream;
}


/*
    Note for == operator: must be overloaded for a couple classes.
    == is already overloaded for vectors of primitive types and for maps of primitive types
*/
// Ballot equality; compare all members
bool operator==(Ballot a, Ballot b) {
    return (a.get_id() == b.get_id()) && (a.get_preference_map() == b.get_preference_map());
}

// Candidate equality; compare all members
bool operator==(Candidate a, Candidate b) {
    return (a.get_name() == b.get_name()) && (b.get_ballots() == a.get_ballots()) && (a.voteCounts() == b.voteCounts());
}

/**************************************************************************/

// Forward declaration of functions and main
void BallotTest();
void CandidateTest();
void DroopTest();
void PluralityTest();

int main() {
    BallotTest();
    CandidateTest();
    DroopTest();
    PluralityTest();

    //////////////////////////////////////////////////////////

    lineClear();
    printf("\nTotal tests passed: %d/%d", TPASS, TCOUNT);
    cout << "\n\n";

    return 0;
}

/**************************************************************************/

// Definitions of tests

/*
    Follow this template; write all tests for a certain function within a bracketed area:

    void ~~~Test() {
        // Test all of ~~~ public functions
        cout << "\n\n";
        cout << "Testing ~~~ class";

        int testCount = 0, testPass = 0;

        {

        }


        lineClear();
        printf("Tests passed: %d/%d\n\n", testPass, testCount);
        lineClear();
    }
*/

void BallotTest() {
    // Test all of ballots public functions
    cout << "\n\n";
    cout << "Testing Ballot class";

    int testCount = 0, testPass = 0;

    {
        // Constructor with two parameters
        map<int, string> p_map;
        p_map[0] = "Test";
        int id = 10;
        Ballot b(p_map, id);

        // Map test
        ASSERT<map<int, string>>(p_map, b.get_preference_map(), "Constructor - Map", testCount, testPass);

        // ID test w/ set id
        ASSERT<int>(id, b.get_id(), "Constructor - ID (set ID)", testCount, testPass);

        // ID test w/ default id
        Ballot c = Ballot(p_map);
        ASSERT<int>(0, c.get_id(), "Constructor - ID (default ID)", testCount, testPass);

        // ID test w/ set id
        ASSERT<map<int, string>>(p_map, b.get_preference_map(), "Get Preference Map", testCount, testPass);

        // Setter test for preference map
        map<int, string> p_map_new;
        p_map_new[0] = "abc";
        b.set_preference_map(p_map_new);
        ASSERT<map<int, string>>(p_map_new, b.get_preference_map(), "Set Preference Map", testCount, testPass);

        // Getter test for ID
        ASSERT<int>(id, b.get_id(), "Get ID", testCount, testPass);

        // Setter test for ID
        b.set_id(30);
        ASSERT<int>(30, b.get_id(), "Set ID", testCount, testPass);
    }


    lineClear();
    printf("Tests passed: %d/%d\n\n", testPass, testCount);
    lineClear();
}


void CandidateTest() {
    // Test all of ~~~ public functions
    cout << "\n\n";
    cout << "Testing Candidate class";

    int testCount = 0, testPass = 0;

    {
        // Constructor
        string name = "TestName";
        Candidate c(name);

        // Name test (set name)
        ASSERT<string>(name, c.get_name(), "Constructor - Name (set name)", testCount, testPass);

        // Name test (default value)
        c = Candidate();
        ASSERT<string>("", c.get_name(), "Constructor - Name (default name - Empty)", testCount, testPass);
	


	
    }

    {
        // Set/Get Ballots
        Candidate c("Name");
        // Construct a ballot vector
        map<int, string> p_map;
        p_map[0] = "Test";
        vector<Ballot> vec;
        vec.push_back(Ballot(p_map));

        // Set and test
        c.set_ballots(vec);
        TEST<vector<Ballot> >(vec, c.get_ballots(), "Set/Get Ballots", testCount, testPass);


	TEST<string>("Name", c.get_name(), "get_Name", testCount, testPass);

	c.set_name("Name1");
	TEST<string>("Name1", c.get_name(), "set_Name", testCount, testPass);
	


        // Testing addBallot
        p_map[3] = "Test add another key";
        Ballot testBal(p_map, 5);
        // Add ballot and also push back on vector
        c.addBallot(testBal);
        vec.push_back(testBal);
        TEST<vector<Ballot> >(vec, c.get_ballots(), "addBallot()", testCount, testPass);

        // Test voteCounts
        TEST<int>(vec.size(), c.voteCounts(), "voteCounts()", testCount, testPass);
    }


    lineClear();
    printf("Tests passed: %d/%d\n\n", testPass, testCount);
    lineClear();
}



void DroopTest() {
    // Test all of Droop public functions
    cout << "\n\n";
    cout << "Testing Droop class";

    int testCount = 0, testPass = 0;

    {
	// Constructor without defalut   
	map<int, string> p_map;
        p_map[0] = "Test";
        int id = 10;
        Ballot b(p_map, id);
	vector<Ballot> b_vector;
	b_vector.push_back(b);

	string name = "TestName";
        Candidate c(name);
	vector<Candidate> c_vector;
	c_vector.push_back(c);
	STV s(b_vector,c_vector);
	 // Constructor
        ASSERT<int>(0, s.get_Seats(), "Constructor - Seat (defalut seats)", testCount, testPass);
        // seat test (set seat)
	int seats = 5; 
        STV s1(b_vector,c_vector, seats);
        ASSERT<int>(seats, s1.get_Seats(), "Constructor - Seat (set seats)", testCount, testPass);
        // Ballot test
        ASSERT<vector<Ballot>>(b_vector, s.get_Ballots(), "Constructor - Ballot (get Ballot)", testCount, testPass);
	 // Candiate test
        ASSERT<vector<Candidate>>(c_vector, s.get_Candidates(), "Constructor - Candidate (get Candidate)", testCount, testPass);

    }

    {
	vector<Ballot> b_vector;
	vector<Candidate> c_vector;
	STV s(b_vector,c_vector);

	//test addWinner, get_winners, addLoser, get_Losers
	TEST<int>(0, s.get_Winners().size(), "get_Winners() (Defalut : No winners)", testCount, testPass);
	TEST<int>(0, s.get_Losers().size(), "get_Losers() (Defalut: No losers)", testCount, testPass);
	

	TEST<int>(0, s.get_Winners().size(), "get_Winners()/ addWinner(Candidate) (add 1 winner does not reach droop)", testCount, testPass);
	string name = "TestName";
        Candidate c(name);
 
	map<int, string> p_map;
        p_map[0] = "Test";
        p_map[3] = "Test add another key";
        Ballot testBal(p_map, 5);
        // Add ballot and also push back on vector
        c.addBallot(testBal);
	s.addWinner(c);
	TEST<int>(1, s.get_Winners().size(), "get_Winners()/ addWinner(Candidate) (add 1 winner reach droop)", testCount, testPass);

	s.addLoser(c);
	TEST<int>(1, s.get_Losers().size(), "get_Losers()/ addLoser(Candidate) (add 1 losers)", testCount, testPass);
	
	map<int, string> p_map1;
        p_map1[0] = "Jacob";
        vector<Ballot> ballots;
        Ballot b(p_map1, 1);
        ballots.push_back(b);
        vector<Candidate> candidates;
	//candidates.set_ballots(ballots);
        Candidate c1("Jacob");
        candidates.push_back(c1);
	
        STV s1(ballots, candidates,1);
	TEST<int>(0, s1.findCandidateIndexByName("Jacob"), "findCandidateIndexByName function", testCount, testPass);
	s1.run();
        TEST<string>("Jacob", s1.get_Winners()[0].get_name(), "Run function", testCount, testPass);
	lineClear();
	// Print result test
        cout << "Testing of printResults function:" << endl;
        cout << "Expected Winner of Seat 1: Jacob (1 votes), got ";
        s1.printResults();
        testCount += 1;
        testPass += 1;
	

     }
    lineClear();
    printf("Tests passed: %d/%d\n\n", testPass, testCount);
    lineClear();
}



void PluralityTest() {
    // Test all of Plurality public functions
    cout << "\n\n";
    cout << "Testing Plurality class";

    int testCount = 0, testPass = 0;

    {
      // Constructor
      map<int, string> p_map;
      p_map[0] = "Jacob";
      vector<Ballot> ballots;
      Ballot b(p_map, 5);
      ballots.push_back(b);
      vector<Candidate> candidates;
      Candidate c("Jacob");
      candidates.push_back(c);
      int seats = 1;
      Plurality p(ballots, candidates, seats);

      // Ballot array test
      ASSERT<vector<Ballot>>(ballots, p.get_Ballots(), "Constructor - Ballot", testCount, testPass);

      // Candidate array test
      ASSERT<vector<Candidate>>(candidates, p.get_Candidates(), "Constructor - Candidate", testCount, testPass);

      // Number of seats test
      ASSERT<int>(seats, p.get_Seats(), "Constructor - # of seats(pass in)", testCount, testPass);

      // Number of seats test
      Plurality p_new(ballots, candidates);
      ASSERT<int>(0, p_new.get_Seats(), "Constructor - # of seats(default)", testCount, testPass);

      // Run function test
      p.run();
      ASSERT<vector<Ballot>>(ballots, p.get_Candidates()[0].get_ballots(), "Run function", testCount, testPass);
      lineClear();

      // Print result test
      cout << "Testing of printResults function:" << endl;
      cout << "Expected Winner of Seat 1: Jacob (1 votes), got ";
      p.printResults();
      testCount += 1;
      testPass += 1;
    }


    lineClear();
    printf("Tests passed: %d/%d\n\n", testPass, testCount);
    lineClear();
}
