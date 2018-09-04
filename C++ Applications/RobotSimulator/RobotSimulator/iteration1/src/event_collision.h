/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_COLLISION_H_
#define SRC_EVENT_COLLISION_H_

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
  * Check the state of collision. i.e Posion, angle, and so on.
  */
class EventCollision : public EventBaseClass {
 public:
  EventCollision();
  void EmitMessage(void);
  /**
   * @brief Get if is is collided with others
   * @return collided bool
   */
  bool get_collided() { return collided_; }
  /**
   * @brief Set the collided is trure if is is collided with others
   * @param c bool
   */
  void set_collided(bool c) { collided_ = c; }
  /**
   * @brief Get the contact point
   * @return point_of_contact_ Position
   */
  Position get_point_of_contact() { return point_of_contact_; }
  /**
   * @brief Set the contact point
   * @param p Position
   */
  void set_point_of_contact(Position p) { point_of_contact_ = p; }
  /**
   * @brief Get the contact angle
   */
  double get_angle_of_contact() { return angle_of_contact_; }
  /**
   * @brief Set the contact angle
   * @param aoc double
   */
  void set_angle_of_contact(double aoc) { angle_of_contact_ = aoc; }


 private:
  bool collided_;
  Position point_of_contact_;
  double angle_of_contact_;
  double speed_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_COLLISION_H_ */
