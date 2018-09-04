/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_PROXIMITY_H_
#define SRC_SENSOR_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>
// #include "src/player.h"
// #include "src/robot.h"
#include "src/position.h"
// #include "src/event_proximity.h"
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
 * @brief A derived class from sensor base class;a representation of a proximity sensor.
 * For our purposes, it is used to detect the distance between this sensor holder
 * to another entity. And also react those different entity as different behavior
 * Those controls are handled by mothion handler
 *
 */
  class SensorProximity : public Sensor {
   public:
     SensorProximity();
   /**
    * @brief Compute a new reading based on the proximity event.
    *
    * Note that proximity events can report "no proximity" which
    * will inactivate the sensor.
    * @return activated_ bool
    */
    int get_activated(void) { return activated_; }
    /**
     * @brief Set a if it has been activated based on the proximity event.
     * @param value bool
     */
    void set_activated(bool value) { activated_ = value; }

    /**
     * @brief Get the current field of view from the sensor.
     */
    double get_fov() { return fov_; }
    /**
     * @brief Set the sensor field of view from the sensor.
     * @param
     */
    void set_fov(double f) { fov_ = f; }

    /**
     * @brief Get the current distance from the sensor.
     * @return double range_
     */
    double get_range() { return range_; }
    /**
     * @brief Set the sensor distance.
     * @param double d
     */
    void set_range(double d) { range_ = d; }
    /**
     * @brief if entities have the collision will hapen in the future in the arena. This event is
     * accepted, to avoid player via motionhandler.
     * @param Pointer to EventProximity e
     */
    void Accept(EventProximity * e);
   /**
    * @brief Reset the proximity sensor to its newly constructed state.
    */
    void Reset(void);
    /**
     * @brief Get the current distance between this entity to the others
     * @return double distance_
     */
    double get_distance() { distance_; }
    /**
     * @brief Set the current distance between this entity to the others
     * @return double d
     */
    void set_distance(double d) { distance_ = d; }
    /**
     * @brief Compute the current distance between this entity to the others
     * -1 means, the other entity
     * is not in this range of sensor, and if the returned value is grater than -1, then we
     * handle the behavior by different situations
     * @param Position p1, Position p2, double ha, double r
     * @return double which indicate the state.
     */
    double sensor_reading(Position p1, Position p2, double ha, double r);
    /**
     * @brief take sensor's information, and sensed entity information to see if it they are in the range
     * It's a  helper functin for sensor_reading.
     * @return bool
     */
    bool in_range(double lower1, double upper1, double lower2, double upper2);

    void Accept(EventTypeEmit * e) { }
    void Accept(EventDistressCall * e) { }
    void Accept(EventCollision * e) { }

   private:
    double range_, fov_, distance_;
    Position p1, p2;
    double heading_angle_, radius_;
    ArenaEntity* sensed_;
    int activated_;
    double speed_;
  };

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_PROXIMITY_H_
