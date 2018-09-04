/**
 * @file event_keypress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_KEYPRESS_H_
#define SRC_EVENT_KEYPRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/event_commands.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A derived event class from Event base class.
  * Check the state of key pressed, and change the velocity and heading angle by changes
  */
class EventKeypress : public EventBaseClass {
 public:
  explicit EventKeypress(int key) : key_(key) {}
  /**
   * @brief When user uses press keys on  key board, then it should emit
   * a message"Keypress command received" to the user on
   * stdout saying what happened, in order to aid debugging.
   *
   */
  void EmitMessage(void) { printf("Keypress command received\n"); }
  /**
   * @brief Get what the value of key is
   * @return key_ int
   */
  int get_key(void) const {return key_;}
  /**
   * @brief Get what the command is
   * @return a enum
   */
  enum event_commands get_key_cmd() const;

 private:
  int key_;

  EventKeypress& operator=(const EventKeypress& other) = delete;
  EventKeypress(const EventKeypress& other) = delete;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_KEYPRESS_H_ */
