/**
  @file candidate.cpp

  @copyright Spring 2018, Team 10 CSci 5801
*/

// Includes
#include "./candidate.h"

// Namespaces
using std::string;
using std::vector;

/**************************************************************************/

Candidate::Candidate(string name) {
  candidate_name = name;
}

vector<Ballot> Candidate::get_ballots() {
  return ballots;
}

void Candidate::set_ballots(vector<Ballot> b) {
  ballots = b;
}

string Candidate::get_name() {
  return candidate_name;
}

void Candidate::set_name(string name) {
  candidate_name = name;
}

void Candidate::addBallot(Ballot b) {
  ballots.push_back(b);
}

int Candidate::voteCounts() {
  return ballots.size();
}
