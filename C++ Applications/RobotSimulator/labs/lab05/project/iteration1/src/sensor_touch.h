/**
 * @file sensor_touch.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_TOUCH_H_
#define SRC_SENSOR_TOUCH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A representation of a touch sensor. Touch or "bump" sensors are
 * "active" when pressed. For our purposes, imagine a series of bump sensors
 * around the perimeter of the robot. A collision will activate the sensor
 * at a particular point of contact, which translates to an angle of contact
 *
 */
class SensorTouch {
 public:
  SensorTouch();

  /**
   * @brief Get the current activation reading from the sensor.
   */
  bool activated(void) { return activated_; }
  void activated(bool value) { activated_ = value; }

  Position point_of_contact() { return point_of_contact_; }
  void point_of_contact(Position p) {
    point_of_contact_.x = p.x;
    point_of_contact_.y = p.y;
  }

  double angle_of_contact(void) { return angle_of_contact_; }
  void angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

  /**
   * @brief Compute a new reading based on the collision event.
   *
   * Note that collision events can report "no collision" which
   * will inactivate the sensor.
   *
   */

  void Accept(EventCollision * e);

  /**
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);

 private:
  bool activated_;
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_SENSOR_TOUCH_H_ */
