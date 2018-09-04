/**
 * @file mobile_arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include "src/arena_entity.h"
#include "src/event_base_class.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A derived class representing an mobile entity within the arena.
  * All entities within the arena know how to :
  * 1. Update themselves each timestep (i.e. in accordance with current velocity
  *    and position).
  * 2. Reset themselves to a newly constructed state. This is so the user can
  *    click the reset button after completing a game and have things work as
  *    expected.
  * 3. Accept different collisions
  */
class ArenaMobileEntity : public ArenaEntity {
 public:
  ArenaMobileEntity(double radius, double collision_delta,
                    const Position& pos, const Color& color) :
      ArenaEntity(radius, pos, color),
      collision_delta_(collision_delta) {}
  /**
   * @brief Get the state of the entity, return True
   *
   * @return Boolean Ture
   */
  bool is_mobile(void) { return true; }
  /**
   * @brief Get the HeadingAngle of the entity
   *
   * @return double
   */
  virtual double get_heading_angle(void) const = 0;
  /**
   * @brief Set the HeadingAngle of the entity
   *
   * @param heading_angle double
   */
  virtual void set_heading_angle(double heading_angle) = 0;
  /**
   * @brief Get the speed of the entity
   *
   * @return double
   */
  virtual double get_speed(void) = 0;
  /**
   * @brief Set the speed of the entity
   *
   * @param  sp double
   */
  virtual void set_speed(double sp) = 0;
  /**
   * @brief Get the collision_delta of user defined
   *
   * @return collision_delta_ double
   */
  double get_collision_delta(void) const { return collision_delta_; }
  /**
   * @brief This to update the position, heading_angle, speed, and so on as the unit time passed in.
   * to make entities looks like moving
   * @param Unit dt
   */
  void TimestepUpdate(uint dt);
  /**
   * @brief if entities have collided in the arena, one of entity is not charge station. Collision is
   * accepted, because it relavate the heading_angle, battery and spped of entities after collision
   * @param Pointer to EventCollision e
   */
  virtual void Accept(EventCollision * e) = 0;
  /**
   * @brief if entities have collided in the arena, one of entity is charge atation. Collision is
   * accepted, because it relavate battery of entities after collision with a charge station
   * @param Pointer to EventRecharge e
   */
  virtual void Accept(EventRecharge * e) = 0;

 private:
  double collision_delta_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_MOBILE_ENTITY_H_ */
