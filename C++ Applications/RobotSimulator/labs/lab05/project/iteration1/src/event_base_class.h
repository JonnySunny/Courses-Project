/**
 * @file event_base_class.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_BASE_CLASS_H_
#define SRC_EVENT_BASE_CLASS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base event class from which all events should derive from.
 */
class EventBaseClass {
 public:
  EventBaseClass(void) {}
  virtual ~EventBaseClass(void) {}

  /**
   * @brief Each event, upon its firing, should emit a message to the user on
   * stdout saying what happened, in order to aid debugging.
   *
   */
  virtual void EmitMessage(void) = 0;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_BASE_CLASS_H_ */
