/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_motion_handler.h"
#include "src/superbot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/sensor_entity_type.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"
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
  * @brief  Robot class is derived from ArenaMobileEntity class. It has sensor touch in this iterattion, and
  * its movement in the Arena sometimes will have collision with the wall and all of entities. That will
  * be handled by mothion handler.
  *
  */
class Robot : public ArenaMobileEntity {
 public:
  explicit Robot(const struct robot_params* const params);
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
  /**
   * @brief if entities have collided or detected the collision will hapen in the future in the arena. This event is
   * accepted.
   * @param Pointer to EventTypeEmit e
   */
  void Accept(EventTypeEmit * e);
  /**
   * @brief if entities have the collision will hapen in the future in the arena. This event is
   * accepted, to avoid player via motionhandler.
   * @param Pointer to EventProximity e
   */
  void Accept(EventProximity * e);
  /**
   * @brief if entities are frezon. This event is
   * accepted and send the distress call to others.
   * @param Pointer to EventDistressCall e
   */
  void Accept(EventDistressCall * e);
  /**
   * @brief User input commands to change heading or speed
   */
  // void EventCmd(enum event_commands cmd);
  /**
   * @brief Get battery level for current robot
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
   * @brief Get id for robot, that will help users to identify the different robots
   *
   * @return id_ int
   */
  int id(void) const { return id_; }
  /**
   * @brief Get name for robot, that will help users to identify the different robots, and
   * also to differentiate whether is has become a Superbot by it name at first glance
   *
   * @return "Robot + id" string
   */
  std::string name(void) const {
    return motion_handler_.get_name() + std::to_string(id());
  }
  /**
   * @brief Set  the name of this rotot to differentiate whether is has become a Superbot
   *
   * @param string s
   */
  void set_name(std::string s) {
    motion_handler_.set_name(s);
  }

  int get_sensor_proximity_state() {
    if (sensor_proximity_.get_activated() == 1) {
      state_proximity_ = 1;
    } else {
      state_proximity_ = 0;
    }
    return state_proximity_;
  }

  int get_sensor_distress_state() {
    if (sensor_distress_.get_activated() == 1) {
      state_distress_ = 1;
    } else {
      state_distress_ = 0;
    }
    return state_distress_;
  }

  double get_fov() {
    return sensor_proximity_.get_fov();
  }

 private:
  std::string name_;
  double heading_angle_;
  double angle_delta_;
  RobotBattery battery_;
  RobotMotionHandler motion_handler_;
  MotionBehavior motion_behavior_;
  SensorDistress sensor_distress_;
  SensorTouch sensor_touch_;
  SensorEntityType sensor_entity_type_;
  SensorProximity sensor_proximity_;
  int state_proximity_;
  int state_distress_;
  int id_;
  static unsigned int next_id_;
};

NAMESPACE_END(csci3081);

#endif  //  SRC_ROBOT_H_
