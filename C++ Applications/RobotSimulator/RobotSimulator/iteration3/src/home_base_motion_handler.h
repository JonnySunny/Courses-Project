/**
 * @file home_base_motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_HOME_BASE_MOTION_HANDLER_H_
#define SRC_HOME_BASE_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/robot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The handler for the homebase's actuators.
 * HomebaseMotionHandler manages the modification to the velocity based on
 * only collisions.
 * MotionBehavior translates velocity and position to a new position.
 * Both of these are straightforward, but the framework allows for more
 * sophisticated models of motion in which each wheel has distinct speed.
 *
 */
class HomeBaseMotionHandler : public MotionHandler {
 public:
  HomeBaseMotionHandler();
  ~HomeBaseMotionHandler() {}
  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  void Reset(void) {
    set_heading_angle(heading_angle_);
    set_max_speed(max_speed_);
    set_speed(5);
  }

  /**
   * @brief Command from user keypress via the viewer.
   *
   * @param cmd The command.
   */
  // void AcceptCommand(enum event_commands cmd);

  /**
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void UpdateVelocity(SensorTouch st);
  /**
   * @brief Get the speed of the entity
   *
   * @return double
   */
  double get_speed() { return speed_; }
  /**
   * @brief Set the speed of the entity
   *
   * @param  sp double
   */
  void set_speed(double sp) {speed_ = sp;}
  /**
   * @brief Get the delta angle, since we want to adjust the heading angle by using this angle_delta
   *
   * @param ab double
   */
  void set_angle_delta(double ab) {angle_delta_ = ab; }
  /**
   * @brief Increase the heading angle by using this angle_delta
   *
   * @param ab double
   */
  void HeadingAngleInc(double ag) { heading_angle_ += ag; }
  /**
   * @brief Decrease the heading angle by using this angle_delta
   *
   * @param ab double
   */
  void HeadingAngleDec(double ag) { heading_angle_ -= ag; }
  /**
   * @brief Get the HeadingAngle of the entity after incre
   *
   * @return double
   */
  double get_heading_angle() const { return heading_angle_;}
  /**
   * @brief Get the HeadingAngle of the entity
   *
   * @param ha double
   */
  void set_heading_angle(double ha) { heading_angle_ = ha; }
  /**
   * @brief Get the max speed of this homebase
   *
   * @return double
   */
  double get_max_speed() { return max_speed_; }
  /**
   * @brief Set the max speed of this homebase
   *
   * @param ms double
   */
  void set_max_speed(double ms) { max_speed_ = ms; }

 private:
  int adjust_angle_;
  double heading_angle_;
  double speed_;
  double max_speed_;
  double angle_delta_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_HOME_BASE_MOTION_HANDLER_H_
