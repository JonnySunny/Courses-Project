/**
 * @file event_distresscall.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_DISTRESSCALL_H_
#define SRC_EVENT_DISTRESSCALL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "position.h"
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
  * To be passed and indiication the state of distresstion.
  */
class EventDistressCall : public EventBaseClass {
 public:
  EventDistressCall(){}
  void EmitMessage(void){}
  /**
   * @brief Get if is is distressed
   * @return collided bool
   */
  bool get_distressed() { return distressed_; }
  /**
   * @brief Set the collided is trure if is is distressed
   * @param c bool
   */
  void set_distressed(bool c) { distressed_ = c; }



 private:
  bool distressed_;

};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_DISTRESSCALL_H_ */
