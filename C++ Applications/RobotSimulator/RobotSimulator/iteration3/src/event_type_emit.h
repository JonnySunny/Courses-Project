/**
 * @file event_typeemit.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_TYPE_EMIT_H_
#define SRC_EVENT_TYPE_EMIT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/position.h"
#include "src/entity_type.h"
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
  * Pasing the information in this event and let entity knows which
  *  other entity it will have colliison with.
  */
class EventTypeEmit : public EventBaseClass {
 public:
  EventTypeEmit() :
    type_(None) {}
  void EmitMessage(void) {}
  /**
   * @brief Get if is is collided with others
   * @return collided bool
   */
  enum entity_type get_entity_type() {
    return type_; }
  /**
   * @brief Set the collided is trure if is is collided with others
   * @param c bool
   */
  void set_entity_type(enum entity_type c) { type_ = c; }


 private:
  enum entity_type type_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_TYPE_EMIT_H_ */
