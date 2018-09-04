/**
  @file ballot.h

  @copyright Spring 2018, Team 10 CSci 5801
*/

#ifndef SRC_BALLOT_H_
#define SRC_BALLOT_H_

// Includes
#include <string>
#include <map>

/**************************************************************************/

/**
 *  @brief This class is used to record each individual voter's ballot, it uses a map to
 *  associate voters' preferences to each candidates with candidates' name. When using droop
 *  algorithm, a ballot need to contain at least half of votes in order to be valid.
 *
 *  Each ballot contain a map and an id which is an integer to identify which ballot it is.
 */
class Ballot {
 private:
  std::map<int, std::string> preference_map;
  int ballot_id;

 public:
  explicit Ballot(std::map<int, std::string> m, int i = 0);

  /**
  * @brief return the preference map which contains votes' preferences and candidates' names
  * @return map<int, string>
  */
  std::map<int, std::string> get_preference_map();

  /**
  * @brief set the value in preference map
  * @param m map<int, string>
  */
  void set_preference_map(std::map<int, std::string> m);

  /**
  * @brief return the id of the current ballot
  * @return int
  */
  int get_id();

  /**
  * @brief set the id of the current ballot
  * @param i int
  */
  void set_id(int i);
};

#endif  // SRC_BALLOT_H_
