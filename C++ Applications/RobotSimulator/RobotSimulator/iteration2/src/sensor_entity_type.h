/**
 * @file sensor_entity_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_ENTITY_TYPE_H_
#define SRC_SENSOR_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>
#include "src/position.h"
// #include "src/event_type_emit.h"
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
 * @brief A derived class from sensor base class;a representation of a entity type sensor. Touch or "bump" sensors are
 * "active" when pressed . For our purposes, imagine a series of bump sensors
 * around the perimeter of the robot. A collision or will have collision in a
 * defined range will activate the sensor
 *
 */
  class SensorEntityType : public Sensor {
   public:
     SensorEntityType();
     ~SensorEntityType() {}
  //  /**
  //   * @brief Compute a new reading based on the Emitype event.
  //   *
  //   * Note that Emitype events can report "no Emitype" which
  //   * will inactivate the sensor.
  //   * @return activated_ bool
  //   */
  //   int get_activated(void) { return activated_; }
  //   /**
  //    * @brief Set a if it has been activated based on the Emitype event.
  //    * @param value bool
  //    */
  //   void set_activated(bool value) { activated_ = value; }


    /**
    * @brief if entities have collided in the arena. Emitype is
    * accepted, because it relavate the heading_angle, and spped of entities after Emitype
    * @param Pointer to EventTypeEmit e
    */
    void Accept(EventTypeEmit * e);
   /**
    * @brief Reset the proximity sensor to its newly constructed state.
    */
    void Reset(void);
    // /**
    //  * @brief Get the current distance from the sensor.
    //  * @return double range_
    //  */
    // double get_range() { return range_; }
    // /**
    //  * @brief Set the sensor distance.
    //  * @param double d
    //  */
    // void set_range(double d) { range_ = d; }
    /**
     * @brief Get the type of detected entity from the sensor.
     * @return entity_type type_
     */
    entity_type get_entity_type(void) {
       return type_; }
     /**
      * @brief Get the type of detected entity from the sensor.
      * @param entity_type e
      */
    void set_entity_type(entity_type e) {
       type_ = e;
     }
    // void Accept(EventDistressCall * e) {}
    // void Accept(EventProximity * e) {}
    // void Accept(EventCollision * e) {}

   private:
    entity_type type_;
  };

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_ENTITY_TYPE_H_
