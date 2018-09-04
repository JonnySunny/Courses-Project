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
class Robot : public ArenaMobileEntity {
 public:
  explicit Robot(const struct robot_params* const params);

  void ResetBattery(void);
  void Reset(void);
  void HeadingAngleInc(void) { heading_angle_ += angle_delta_; }
  void HeadingAngleDec(void) { heading_angle_ -= angle_delta_; }
  void TimestepUpdate(unsigned int dt);
  void Accept(EventRecharge * e);
  void Accept(EventCollision * e);
  void EventCmd(enum event_commands cmd);

  double battery_level(void) { return battery_.level(); }
  double heading_angle(void) const { return motion_handler_.heading_angle(); }
  void heading_angle(double ha) { motion_handler_.heading_angle(ha); }
  double speed(void) { return motion_handler_.speed(); }
  void speed(double sp) { motion_handler_.speed(sp); }
  int id(void) const { return id_; }
  Position pos() const { return pos_; }
  void pos(Position pos) { pos_ = pos; }
  std::string name(void) const {
    return "Robot" + std::to_string(id());
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
  Position pos_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ROBOT_H_ */
