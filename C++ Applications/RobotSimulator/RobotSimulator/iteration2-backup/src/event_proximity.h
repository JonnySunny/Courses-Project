/**
 * @file event_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_PROXIMITY_H_
#define SRC_EVENT_PROMIXITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "position.h"



/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A derived event class from Event base class.
  * Check the disrance of two entities. Need some entity information i.e Posion, angle, and so on.
  */
class EventProximity : public EventBaseClass {
 public:
  EventProximity() {};
  void EmitMessage(void) {}
  /**
   * @brief Get the Position of entity who has proximixiy sensor
   * @return Postion p1
   */
  Position get_posiiton_of_sensor(void) { return p1; }
  /**
   * @brief Set the Position for the first entity which
   * has this proximixiy sensor
   * @param Position a
   */
  void set_position_of_sensor(Position a) { p1 = a; }
  /**
   * @brief Get the Position of entity who has been sensed or intended to be sensed
   * @return Postion p2
   */
  Position get_position_of_sensed(void) { return p2; }
  /**
   * @brief Set the Position for the sencond entity, which also
   * is a sensed entity if it is in the range.
   * @param Position a
   */
  void set_position_of_sensed(Position p) { p2 = p; }

  /**
   * @brief Get the heading_angle_ of entity who has proximixiy sensor
   * @return double heading_angle_
   */
  double get_heading_angle_of_sensor(void) { return heading_angle_; }
  /**
   * @brief Set the heading_angle_ for the first entity which
   * has this proximixiy sensor
   * @param double a
   */
  void set_heading_angle_of_sensor(double a) { heading_angle_ = a; }
  /**
   * @brief Get the radius of entity who has been sensed or intended to be sensed
   * @return double radius.
   */
  double get_radius_of_sensed(void) { return radius_; }
  /**
   * @brief Set the radius for the sencond entity, which also
   * is a sensed entity if it is in the range.
   * @param double a
   */
  void set_radius_of_sensed(double a) { radius_ = a; }



 private:
  Position p1, p2;
  double radius_, heading_angle_;
  // Robot * sensor_;
  // ArenaMobileEntity* sensor_;
  // ArenaEntity * sensed_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_EVENT_PROMIXITY_H_ */
