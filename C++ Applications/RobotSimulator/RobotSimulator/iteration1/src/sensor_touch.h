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
#include "src/position.h"
#include "src/event_collision.h"
#include "src/sensor_base.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A derived class from sensor base class;a representation of a touch sensor. Touch or "bump" sensors are
 * "active" when pressed. For our purposes, imagine a series of bump sensors
 * around the perimeter of the robot. A collision will activate the sensor
 * at a particular point of contact, which translates to an angle of contact
 *
 */
  class SensorTouch : public Sensor {
   public:
     SensorTouch();
   /**
    * @brief Compute a new reading based on the collision event.
    *
    * Note that collision events can report "no collision" which
    * will inactivate the sensor.
    * @return activated_ bool
    */
    bool get_activated(void) { return activated_; }
    /**
     * @brief Set a if it has been activated based on the collision event.
     * @param value bool
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

    /**
     * @brief if entities have collided in the arena. Collision is
     * accepted, because it relavate the heading_angle, and spped of entities after collision
     * @param Pointer to EventCollision e
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
    Position point_of_ent1_central_;
    Position point_of_ent2_central_;
    double distance_;
    double speed_;
  };

NAMESPACE_END(csci3081);

#endif   /* SRC_SENSOR_TOUCH_H_ */
