/**
 * @file sensor_entity_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_DISTRESS_H_
#define SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>
#include "src/position.h"
// #include "src/event_distresscall.h"
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
 * @brief A derived class from sensor base class;a representation of a distress sensor. Touch or "bump" sensors are
 * "active" when this entity is freeze. For our purposes, imagine a series of bump sensors
 * around the perimeter of the robot. A special collision will inactivate the sensor
 * at a particular point of contact and also unfreeze this entity.
 *
 */
  class SensorDistress : public Sensor {
   public:
     SensorDistress();
   /**
    * @brief Compute a new reading based on the distress event.
    *
    * Note that distress events can report "no distress" which
    * will inactivate the sensor.
    * @return activated_ bool
    */
    int get_activated() { return activated_; }
    /**
     * @brief Set a if it has been activated based on the distress event.
     * @param value bool
     */
    void set_activated(bool value) { activated_ = value; }

    /**
    * @brief if entities have collided in the arena. distress is
    * accepted, because it relavate the heading_angle, and spped of entities after distress
    * @param Pointer to EventDistressCall e
    */
    void Accept(EventDistressCall * e);
   /**
    * @brief Reset the proximity sensor to its newly constructed state.
    */
    void Reset(void);

    // void set_distress_call(bool d){distress_call_ = d;}
    /**
    * @brief set the range of this sensor
    * @param double r
    */
    void set_range(double r) { range_ = r; }
    /**
    * @brief Set the range of this sensor
    * @return double range_
    */
    double get_range(void) { return range_; }

    void Accept(EventTypeEmit * e) {}
    void Accept(EventProximity * e) {}
    void Accept(EventCollision * e) {}

   private:
    double range_;
    int activated_;
  };

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_DISTRESS_H_
