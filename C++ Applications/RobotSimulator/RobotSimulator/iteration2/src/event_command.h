/**
 * @file actuator_cmd_event.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_COMMAND_H_
#define SRC_EVENT_COMMAND_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/event_commands.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base event class from which all visitor-enabled events should
 * derived from.
 */
class EventCommand : public EventBaseClass {
 public:
  explicit EventCommand(enum event_commands cmd) : cmd_(cmd) {}
  /**
   * @brief When user has command, then it should emit a message"Motion cmd received" to the user on
   * stdout saying what happened, in order to aid debugging.
   *
   */
  // void EmitMessage(void) { printf("Motion cmd %d received\n", cmd_); }
  /**
   *
   * @brief When user uses Command on the key board, it will return a event_commands structor.
   * This structor includes COM_TURN_LEFT,COM_TURN_RIGHT, COM_SPEED_UP, COM_SLOW_DOWN
   *
   */
  enum event_commands cmd(void) const { return cmd_; }

 private:
  enum event_commands cmd_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_EVENT_COMMAND_H_
