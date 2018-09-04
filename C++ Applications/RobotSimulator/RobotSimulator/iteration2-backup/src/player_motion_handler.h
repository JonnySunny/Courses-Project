/**
 * @file player_motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_MOTION_HANDLER_H_
#define SRC_PLAYER_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/robot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/entity_type.h"
#include "src/motionhandler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The handler for the Player's actuators, which in this case are the two
 * wheel actuators. Its main job is to translate the directional commands from
 * the user into the appropriate differential drive wheel speeds.
 *
 * rMotionHandler manages the modification to the velocity based on
 * user input and collisions.
 * PlayerMotionBehavior translates velocity and position to a new position.
 * Both of these are straightforward, but the framework allows for more
 * sophisticated models of motion in which each wheel has distinct speed.
 *
 * For this iteration, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class PlayerMotionHandler : public MotionHandler {
 public:
  PlayerMotionHandler();

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
  void AcceptCommand(enum event_commands cmd);

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
   * @brief Get the max speed of this Player
   *
   * @return double
   */
  double get_max_speed() { return max_speed_; }
  /**
   * @brief Set the max speed of this Player
   *
   * @param ms double
   */
  void set_max_speed(double ms) { max_speed_ = ms; }

  /**
   * @brief Set the type of this Player would have collisions
   *
   * @param entity_type t
   */
void set_type(entity_type t) {t_ = t;}
 /**
  * @brief Get the type of this Player would have collisions
  *
  * @return entity_type t_
  */
  entity_type get_type() { t_; }

 private:
  entity_type t_;
  double heading_angle_;
  double speed_;
  double max_speed_;
  double angle_delta_;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_PLAYER_MOTION_HANDLER_H_ */
