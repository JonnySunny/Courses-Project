/**
 * @file sensor_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_BASE_H_
#define SRC_SENSOR_BASE_H_

#include <limits>
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/**
 * @brief The base class, other class can be derived from it
 *
 */
class Sensor {
 public:
  Sensor() {}
  /**
   * @brief Get the current activation reading from the sensor.
   */
  bool get_activated(void) { return activated_; }
  /**
   * @brief Set the current activation reading from the sensor.
   * @param
   */
  void set_activated(bool value) { activated_ = value; }
  /**
   * @brief Get the contact point
   */
  Position get_point_of_contact() { return point_of_contact_; }
  /**
   * @brief Set the contact point
   * @param p Position
   */
  void set_point_of_contact(Position p) {
    point_of_contact_.x = p.x;
    point_of_contact_.y = p.y;
  }
  /**
   * @brief Get the contact angle
   */
  double get_angle_of_contact(void) { return angle_of_contact_; }
  /**
   * @brief Set the contact angle
   * @param aoc double
   */
  void set_angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

 private:
  bool activated_;
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_SENSOR_BASE_H_ */
