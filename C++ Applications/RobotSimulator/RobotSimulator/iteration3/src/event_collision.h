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
#include "src/position.h"
#include "src/event_base_class.h"
#include "src/arena_entity.h"



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
  /**
   * @brief Set the first Entity
   * @param ent1 pointer to an ArenaEntity
   */
  //
  // void set_ent1(ArenaEntity* ent1) { ent1_ = ent1; }
  // /**
  //  * @brief return the first Entity
  //  * @return pointer of a ArenaEntity ent1_
  //  */
  // ArenaEntity * get_ent1() { return ent1_; }
  // /**
  //  * @brief Set the second Entity
  //  * @param ent1 pointer to an ArenaEntity
  //  */
  // void set_ent2(ArenaEntity* ent2) { ent2_ = ent2; }
  // /**
  //  * @brief return the second  Entity
  //  * @return pointer of a ArenaEntity ent2_
  //  */
  // ArenaEntity * get_ent2() { return ent2_; }
  // /**
  //  * @brief Set the x_dim which is read from arean
  //  * @param double x
  //  */
  // void set_x_dim(double x){x_ = x;}
  // /**
  //  * @brief Set the x_dim which is read from arean
  //  * @return int x_
  //  */
  // double get_x_dim(){return x_;}
  // /**
  //  * @brief Set the y_dim which is read from arean
  //  * @param double y
  //  */
  // void set_y_dim(double y){y_ = y;}
  // /**
  //  * @brief Set the x_dim which is read from arean
  //  * @return int y_
  //  */
  // double get_y_dim(){return y_;}
  // EventCollision& operator=(const EventCollision& other) = delete;
  // EventCollision(const EventCollision& other) = delete;

 private:
  double x_, y_;
  ArenaEntity * ent1_;
  ArenaEntity * ent2_;
  bool collided_;
  Position point_of_contact_;
  double angle_of_contact_;
  // double speed_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_COLLISION_H_
