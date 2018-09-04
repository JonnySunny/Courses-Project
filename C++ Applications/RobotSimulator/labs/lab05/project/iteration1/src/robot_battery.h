/**
 * @file robot_battery.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_BATTERY_H_
#define SRC_ROBOT_BATTERY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The battery for a robot.
 * @todo: implement depletion for movement and collision
 */
class RobotBattery {
 public:
  explicit RobotBattery(double max_charge) : charge_(max_charge),
                                             max_charge_(max_charge) {}

  /**
   * @brief All robots consume SOME power, even when just sitting there not moving.
   */
  double kBASE_DEPLETION = 0.1;

  /**
   * @brief The amount of energy consumed by the robot due to its linear speed
   * its is directly proportional to that speed, with a scaling factor.
   */
  double kLINEAR_SCALE_FACTOR = 0.01;

  /**
   * @brief The amount of energy consumed by the robot due to its angular speed
   * its is directly proportional to that speed, with a scaling factor.
   */
  double kANGULAR_SCALE_FACTOR = 0.01;

  /**
   * @brief Get the current battery level.
   */
  double level(void) const { return charge_; }

  /**
   * @brief Handle a recharge event by instantly restoring the robot's battery
   * to its maximum value.
   */
  void EventRecharge(void) { charge_ = max_charge_; }

  /**
   * @brief Reset the robot's battery to its newly constructed/undepleted state.
   */
  void Reset(void) { EventRecharge(); }

  /**
   * @brief Calculate the new battery level based on the current linear/angular speed.
   *
   * @param linear_vel The current linear speed, in m/s.
   * @param angular_vel The current angular speed, in rad/s.
   *
   * @return The updated battery level.
   */
  double Deplete(__unused Position old_pos,
    __unused Position new_pos, __unused double dt);

  // This is how the battery can be informed a collision occured.
  // Deplete accordingly.
  void Accept(EventCollision * e);

 private:
  double charge_;
  double max_charge_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_ROBOT_BATTERY_H_
