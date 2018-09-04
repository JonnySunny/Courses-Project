/**
  @file candidate.h

  @copyright Spring 2018, Team 10 CSci 5801
*/

#ifndef SRC_CANDIDATE_H_
#define SRC_CANDIDATE_H_

// Includes
#include <string>
#include <vector>
#include "./ballot.h"

/**************************************************************************/

/**
 *  @brief This class is used to represent each individual candidate. It includes each candidate's name and
 *  information about those ballots that got assigned to this candidate.
 *
 */
class Candidate {
 private:
  std::string candidate_name;
  std::vector<Ballot> ballots;

 public:
  explicit Candidate(std::string name = "");

  /**
  * @brief return all the ballots that got assigned to the current candidate
  * @return vector<Ballot>
  */
  std::vector<Ballot> get_ballots();

  /**
  * @brief set the value of the ballot vector
  * @param b vector<Ballot>
  */
  void set_ballots(std::vector<Ballot> b);

  /**
  * @brief return the name of the current candidate
  * @return string
  */
  std::string get_name();

  /**
  * @brief set the name value of the current candidate
  * @param name string
  */
  void set_name(std::string name);

  /**
  * @brief add a single ballot to the ballot vector that belongs to this candidate
  * @param b Ballot
  */
  void addBallot(Ballot b);

  /**
  * @brief return the total number of votes assigned to the current candidate
  * @return int
  */
  int voteCounts();
};

#endif  // SRC_CANDIDATE_H_
