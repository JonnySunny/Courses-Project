/**
 * @file event_recharge.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_RECHARGE_H_
#define SRC_EVENT_RECHARGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A derived event class from Event base class.
  * Check the state of battery, and recharge battery when robot have a collision with recharge station 
  */
class EventRecharge : public EventBaseClass {
 public:
  EventRecharge(void) {}
  /**
   * @brief When robot has collision with charge station, then it should emit
   * a message""Robot Battery recharged!" to the user on
   * stdout saying what happened, in order to aid debugging.
   *
   */
  void EmitMessage(void) { printf("Robot Battery recharged!\n"); }
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_RECHARGE_H_ */
