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
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/robot_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a mobile robot within the arena.
 *
 * Robots have the capability of updating their own position when asked, and
 * also track their own velocity and heading. They have a touch sensor for
 * responding to collision events which is activated/deactivated on collision
 * events.
 *
 */
class Robot : public ArenaMobileEntity {
 public:
  explicit Robot(const struct robot_params* const params);

  /**
   * @brief Reset the robot's battery to full after an encounter with the
   * recharge station.
   */
  void ResetBattery(void);

  /**
   * @brief Reset the robot to a newly constructed state (needed for reset
   * button to work in arena GUI).
   */
  void Reset(void) override;

  /**
   * @brief Update the robot's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Accept a recharge event.
   *
   * This causes the robot's battery to become fully charged.
   *
   * @param e The recharge event.
   */
  void Accept(const EventRecharge * const e) override;

  /**
   * @brief  Pass along a collision event (from arena) to the touch sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The robot's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The collision event.
   */
  void Accept(const EventCollision * const e) override;

  /**
   * @brief Handle user input commands to change the heading or speed.
   *
   * @param cmd The command to process.
   */
  void EventCmd(enum event_commands cmd);

  /**
   * @brief Get the current battery level of the robot.
   */
  double battery_level(void) { return battery_.level(); }
  double heading_angle(void) const override { return motion_handler_.heading_angle(); }
  void heading_angle(double ha) override { motion_handler_.heading_angle(ha); }
  double get_speed(void) const override { return motion_handler_.speed(); }
  void set_speed(double sp) override { motion_handler_.speed(sp); }
  std::string get_name(void) const override {
    return "Robot" + std::to_string(id_);
  }

 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;
  double angle_delta_;
  RobotBattery battery_;
  RobotMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ROBOT_H_ */
