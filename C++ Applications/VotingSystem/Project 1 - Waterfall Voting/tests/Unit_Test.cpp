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
#include "../src/input.h"
#include "../src/result.h"
#include "../src/plurality.h"
using namespace std;

struct greater_than_vote
{
  inline bool operator() (Candidate c1, Candidate c2)
  {
    return (c1.voteCounts() > c2.voteCounts());
  }
};

int main() {
  Result result;
  Input input;
  vector<Candidate> candidates;
  vector<Ballot> ballots;

  Candidate c1 ("x");
  Candidate c2 ("y");
  Candidate c3 ("z");
  candidates.push_back(c1);
  candidates.push_back(c2);
  candidates.push_back(c3);

  cout << "Test Candidate Class: " << endl;
  cout << endl;
  cout << "Candidates names: " << endl;

  for(unsigned int i=0; i<candidates.size(); i++) {
    cout << candidates[i].get_name() << endl;
  }
  cout << endl;

  map<int, string> map1;

  for(unsigned int i=0; i<candidates.size(); i++) {
      map1.insert(pair<int, string> (i+1, candidates[i].get_name()));
  }


  cout << "Test Map: " << endl;
  map <int, string> :: iterator itr;
  cout << "\nThe map is : \n";
  cout << "\tKEY\tELEMENT\n";
  for (itr = map1.begin(); itr != map1.end(); itr++)
  {
      cout  <<  '\t' << itr->first
            <<  '\t' << itr->second << '\n';
  }
  cout << endl;

  Ballot b1(map1, 1);
  ballots.push_back(b1);
  cout << "Ballot ID: " << ballots[0].get_id() << endl;

  Candidate c4 ("a");
  Candidate c5 ("b");
  Candidate c6 ("c");
  Candidate c7 ("d");
  Candidate c8 ("e");
  candidates.push_back(c4);
  candidates.push_back(c5);
  candidates.push_back(c6);
  candidates.push_back(c7);
  candidates.push_back(c8);

  map<int, string> map2;

  for(unsigned int i=0; i<5; i++) {
      map2.insert(pair<int, string> (i+1, candidates[i+3].get_name()));
  }

  cout << "\nThe map is : \n";
  cout << "\tKEY\tELEMENT\n";
  for (itr = map2.begin(); itr != map2.end(); itr++)
  {
      cout  <<  '\t' << itr->first
            <<  '\t' << itr->second << '\n';
  }
  cout << endl;

  Ballot b2(map2, 2);
  ballots.push_back(b2);
  cout << "Ballot ID: " << ballots[1].get_id() << endl;
  cout << endl;
  map<int, string> test_ballot = ballots[0].get_preference_map();
  int id = ballots[0].get_id();

  // map <int, string> :: iterator itr;
  cout << "Test Ballot Class: " << endl;
  cout << endl;
  cout << "Ballot 1: " << endl;
  for (itr = test_ballot.begin(); itr != test_ballot.end(); itr++)
  {
      cout  <<  '\t' << itr->first
            <<  '\t' << itr->second << '\n';
  }
  cout << endl;
  cout << "Ballot ID(inside): " << id <<endl;
  cout << endl;

  test_ballot = ballots[1].get_preference_map();
  id = ballots[1].get_id();
  cout << "Ballot 2: " << endl;
  for (itr = test_ballot.begin(); itr != test_ballot.end(); itr++)
  {
      cout  <<  '\t' << itr->first
            <<  '\t' << itr->second << '\n';
  }
  cout << endl;
  cout << "Ballot ID(inside): " << id << endl;
  cout << endl;

  cout << "Test addBallot: " << endl;
  Candidate c_test("Test addBallot");
  c_test.addBallot(b2);
  Ballot b_test = c_test.get_ballots()[0];
  cout << "Ballot 2: " << endl;
  for (itr = test_ballot.begin(); itr != test_ballot.end(); itr++)
  {
      cout  <<  '\t' << itr->first
            <<  '\t' << itr->second << '\n';
  }
  cout << endl;
  cout << "Ballot ID(inside): " << id << endl;
  cout << endl;



  map<int, string> map3;
  for(unsigned int i=0; i<candidates.size(); i++) {
      map3.insert(pair<int, string> (i+1, candidates[i].get_name()));
  }
  Ballot b3(map3, 3);
  ballots.push_back(b3);

  map<int, string> map4;
  for(unsigned int i=0; i<candidates.size(); i++) {
      map4.insert(pair<int, string> (i+1, candidates[i].get_name()));
  }
  Ballot b4(map4, 4);
  ballots.push_back(b4);

  map<int, string> map5;
  for(unsigned int i=0; i<5; i++) {
      map5.insert(pair<int, string> (i+1, candidates[i+3].get_name()));
  }
  Ballot b5(map5, 5);
  ballots.push_back(b5);

  map<int, string> map6;
  for(unsigned int i=0; i<6; i++) {
      map6.insert(pair<int, string> (i+1, candidates[i+2].get_name()));
  }
  Ballot b6(map6, 6);
  ballots.push_back(b6);

  map<int, string> map7;
  for(unsigned int i=0; i<4; i++) {
      map7.insert(pair<int, string> (i+1, candidates[i+4].get_name()));
  }
  Ballot b7(map7, 7);
  ballots.push_back(b7);

  map<int, string> map8;
  for(unsigned int i=0; i<3; i++) {
      map8.insert(pair<int, string> (i+1, candidates[i+5].get_name()));
  }
  Ballot b8(map8, 8);
  ballots.push_back(b8);

  map<int, string> map9;
  for(unsigned int i=0; i<4; i++) {
      map9.insert(pair<int, string> (i+1, candidates[i+4].get_name()));
  }
  Ballot b9(map9, 9);
  ballots.push_back(b9);

  map<int, string> map10;
  for(unsigned int i=0; i<7; i++) {
      map10.insert(pair<int, string> (i+1, candidates[i+1].get_name()));
  }
  Ballot b10(map10, 10);
  ballots.push_back(b10);



  input.set_num_seats(6);
  input.set_num_ballots(10);
  input.set_num_candidates(8);
  input.set_algorithm(1);

  cout << "Test Input Class: " << endl;
  cout << endl;
  cout << "Number of ballots: " << input.get_num_ballots() << endl;
  cout << "Number of candidates: " << input.get_num_candidates() << endl;
  cout << "Number of seats: " << input.get_num_seats() << endl;
  cout << "Choose of algorithm: " << input.get_algorithm() << endl;
  cout << endl;

  cout << "Test Plurality Class: " << endl;
  cout << endl;
  Plurality p (ballots, result, input, candidates);
  p.assign_ballot();
  p.generate_result();
  result = p.get_result();

  cout << "Test assign_ballot and voteCounts: " << endl;
  vector<Candidate> temp = p.get_candidates_array();
  cout << temp[0].get_name() << ", " << temp[0].voteCounts() << endl;
  cout << temp[1].get_name() << ", " << temp[1].voteCounts() << endl;

  cout << "Test Result Class: " << endl;
  cout << endl;


  vector<Candidate> winners = result.get_winner_list();
  for (unsigned int i=0; i < winners.size(); i++) {
      cout << "The " << i+1 << " winner's name is: " << winners[i].get_name()
      << " and his/her assigned ballots are: ";
    vector<Ballot> ballot_report = winners[i].get_ballots();
    for (unsigned int j=0; j<ballot_report.size(); j++) {
      cout << ballot_report[j].get_id() << " ";
    }
    cout << std::endl;
  }
  cout << std::endl;

  vector<Candidate> losers = result.get_loser_list();
  for (unsigned int i=0; i < losers.size(); i++) {
      cout << "The " << i+1 << " loser's name is: " << losers[i].get_name();
    vector<Ballot> ballot_report_l = losers[i].get_ballots();
    for (unsigned int j=0; j<ballot_report_l.size(); j++) {
      cout << ballot_report_l[j].get_id() << " ";
    }
    cout << std::endl;
  }
  cout << std::endl;

  return 0;
}
