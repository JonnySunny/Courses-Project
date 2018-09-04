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
#include "src/event_base_class.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A collision event class, which is created after a
 * \ref MobileArenaEntity gets within a specified distance of another entity in
 * the arena, OR when an entity that was previously within the collision delta
 * of other entity outside of that threshold.
 */
class EventCollision : public EventBaseClass {
 public:
  EventCollision(void);
  void EmitMessage(void) override;

  /**
   * @brief If \c TRUE, then this instance represents an active collision
   * event. If \c FALSE, then it represents a previous collision event that has
   * been resolved.
   */
  bool collided(void) const { return collided_; }
  void collided(bool c) { collided_ = c; }

  /**
   * @brief The point in the arena at which the entities have collided/touched.
   */
  Position point_of_contact(void) const { return point_of_contact_; }
  void point_of_contact(Position p) { point_of_contact_ = p; }

  /**
   * @brief The angle, in degrees, as specified on the unit circle, that the
   * collision occurred at. Needed to calculate the outgoing/bounceback angle.
   */
  double angle_of_contact(void) const { return angle_of_contact_; }
  void angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

 private:
  bool collided_;
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_COLLISION_EVENT_H_ */
