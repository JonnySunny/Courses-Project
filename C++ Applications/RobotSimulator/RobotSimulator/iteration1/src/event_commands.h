/**
 * @file actuator_commands.h
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 */

#ifndef SRC_EVENT_COMMANDS_H_
#define SRC_EVENT_COMMANDS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
enum event_commands {
  COM_TURN_LEFT,
  COM_TURN_RIGHT,
  COM_SPEED_UP,
  COM_SLOW_DOWN
};
NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_COMMANDS_H_ */
