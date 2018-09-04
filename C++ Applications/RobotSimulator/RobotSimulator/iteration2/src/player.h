/**
 * @file Player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/player_params.h"
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/player_motion_handler.h"
#include "src/sensor_touch.h"
#include "src/robot_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/event_type_emit.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief  Player class is derived from ArenaMobileEntity class. It has sensor touch and battery, and
  * its movement in the Arena sometimes will have collision with the wall and immobile entities. That will
  * be handled by mothion handler.
  *
  */
class Player : public ArenaMobileEntity {
 public:
  explicit Player(const struct player_params* const params);
  /**
   * @brief Reset the battery
   *
   */
  void ResetBattery(void);
  /**
   * @brief Reset ever
   *
   */
  void Reset(void);
  /**
   * @brief Increase By angle_delta_
   */
  void HeadingAngleInc(void) { motion_handler_.HeadingAngleInc(angle_delta_); }
  /**
   * @brief Decrease By angle_delta_
   */
  void HeadingAngleDec(void) { motion_handler_.HeadingAngleDec(angle_delta_); }
  /**
   * @brief This to update the position, heading_angle, speed, and so on as the unit time passed in.
   * to make entities looks like moving
   * @param dt unsigned int
   */
  void TimestepUpdate(unsigned int dt);
  /**
   * @brief if entities have collided in the arena, one of entity is charge atation. Collision is
   * accepted, because it relavate battery of entities after collision with a charge station
   * @param Pointer to EventRecharge e
   */
  void Accept(EventRecharge * e);
  /**
   * @brief if entities have collided in the arena. Collision is
   * accepted, because it relavate the heading_angle, and spped of entities after collision
   * @param Pointer to EventCollision e
   */
  void Accept(EventCollision * e);
  // /**
  //  * @brief if entities have collided in the arena. Collision is
  //  * accepted, because it relavate the heading_angle, and spped of entities after collision
  //  * @param Pointer to EventCollision e
  //  */
  // void Accept(EventTypeEmit * e) {}
  /**
   * @brief User input commands to change heading or speed
   */
  void EventCmd(enum event_commands cmd);
  /**
   * @brief Get battery level for current Player
   *
   */
  double battery_level(void) { return battery_.level(); }
  /**
   * @brief Get the HeadingAngle of the entity
   *
   * @return double
   */
  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle(); }
  /**
   * @brief Set the HeadingAngle of the entity
   *
   * @param ha double
   */
  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }
  /**
   * @brief Get the speed of the entity
   *
   * @return double
   */
  double get_speed(void) { return motion_handler_.get_speed(); }
  /**
   * @brief Set the speed of the entity
   *
   * @param  sp double
   */
  void set_speed(double sp) { motion_handler_.set_speed(sp); }
  /**
   * @brief Get id for Player, that will help users to identify the different Players
   *
   * @return id_ int
   */
  int id(void) const { return id_; }
  /**
   * @brief Get name for Player, that will help users to identify the different Players
   *
   * @return "Player + id" string
   */
  std::string name(void) const {
    return "Player" + std::to_string(id());
  }
  /**
   * @brief Set name for Player, might not use it in the player class
   */
  // void set_name(std::string s) { }

  int get_freeze_time() { return freeze_time_;}

 private:
  RobotBattery battery_;
  double heading_angle_;
  double angle_delta_;
  PlayerMotionHandler motion_handler_;
  MotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  int freeze_time_;
  int id_;
  static unsigned int next_id_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_PLAYER_H_ */
