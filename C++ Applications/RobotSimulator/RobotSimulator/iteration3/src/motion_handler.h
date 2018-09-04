/**
 * @file motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_H_
#define SRC_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/robot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief
 * A base class for various motion handlers
 * The handler for the Entities's actuators, which in this case are the two
 * wheel actuators. Its main job is to translate the directional commands from
 * the user into the appropriate differential drive wheel speeds.
 *
 * MotionBehavior translates velocity and position to a new position.
 * Both of these are straightforward, but the framework allows for more
 * sophisticated models of motion in which each wheel has distinct speed.
 *
 */
class MotionHandler {
 public:
  MotionHandler() :
  heading_angle_(0),
  speed_(0),
  max_speed_(0),
  angle_delta_(0) {}
  virtual ~MotionHandler() = default;
  /**
   * @brief Reset  the actuators to their newly constructed/un-commanded state.
   */
  virtual void Reset(void) = 0;

  // /**
  //  * @brief Command from user keypress via the viewer.
  //  *
  //  * @param cmd The command.
  //  */
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
  void set_speed(double sp) {speed_ = sp; }
  /**
   * @brief Get the delta angle, since we want to adjust the heading angle by using this angle_delta
   *
   * @param ab double
   */
  void set_angle_delta(double ab) {angle_delta_ = ab; }
  // /**
  //  * @brief Increase the heading angle by using this angle_delta
  //  *
  //  * @param ab double
  //  */
  // void HeadingAngleInc(double ag) { heading_angle_ += ag; }
  // /**
  //  * @brief Decrease the heading angle by using this angle_delta
  //  *
  //  * @param ab double
  //  */
  // void HeadingAngleDec(double ag) { heading_angle_ -= ag; }
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
   * @brief Get the max speed of this Entities
   *
   * @return double
   */
  double get_max_speed() { return max_speed_; }
  /**
   * @brief Set the max speed of this Entities
   *
   * @param ms double
   */
  void set_max_speed(double ms) { max_speed_ = ms; }





 private:
  double heading_angle_;
  double speed_;
  double max_speed_;
  double angle_delta_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_MOTION_HANDLER_H_
