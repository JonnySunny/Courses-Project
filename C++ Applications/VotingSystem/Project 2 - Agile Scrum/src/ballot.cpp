/**
  @file ballot.cpp

  @copyright Spring 2018, Team 10 CSci 5801
*/

// Includes
#include "./ballot.h"

// Namespaces
using std::map;
using std::string;

/**************************************************************************/

Ballot::Ballot(map<int, string> m, int i) {
  preference_map = m;
  ballot_id = i;
}

map<int, string> Ballot::get_preference_map() {
  return preference_map;
}

void Ballot::set_preference_map(map<int, string> m) {
  preference_map = m;
}

int Ballot::get_id() {
  return ballot_id;
}

void Ballot::set_id(int i) {
  ballot_id = i;
}
