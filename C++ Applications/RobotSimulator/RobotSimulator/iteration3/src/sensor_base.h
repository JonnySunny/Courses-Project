/**
 * @file sensor_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_BASE_H_
#define SRC_SENSOR_BASE_H_

#include <limits>
#include "src/event_base_class.h"
#include "src/event_collision.h"
#include "src/event_distresscall.h"
#include "src/event_proximity.h"
#include "src/event_type_emit.h"
// #include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/**
 * @brief The base sensor class, other class can be derived from it, to implement more
 *  specific stuff. Such as, proximity, entity_type, touch, distress and so on.
 *
 */
class Sensor {
 public:
  Sensor():
    activated_(false) {}
  virtual ~Sensor() = default;

  /**
   * @brief Get the current activation reading from the sensor.
   */
  bool get_activated() { return activated_; }
  /**
   * @brief Set the current activation reading from the sensor.
   * @param
   */
  void set_activated(bool value) { activated_ = value; }
  /**
   * @brief ReSet the sensor
   * @param
   */
  virtual void Reset() = 0;
  /**
  * @brief if entities have collided in the arena. Collision is
  * accepted, it should be implementted in the derived class.
  * @param Pointer to EventCollision e
  */
  virtual void Accept(EventCollision * e) {
    e->get_collided();
  }

  // /**
  //  * @brief if entities have collided in the
  //  * arena, one of entity is charge atation. Collision is
  //  * accepted, because it relavate battery of entities
  //  * after collision with a charge station
  //  * @param Pointer to EventRecharge e
  //  */
  // virtual void Accept(EventRecharge * e) = 0;

  /**
   * @brief if entities have the collision will hapen in the future in the arena. This event is
   * accepted, to avoid player via motionhandler.
   * @param Pointer to EventProximity e
   */
  virtual void Accept(EventProximity * e) {
    e->get_radius_of_sensed();
  }
  /**
   * @brief if entities are frezon. This event is
   * accepted and send the distress call to others.
   * @param Pointer to EventDistressCall e
   */
  virtual void Accept(EventDistressCall * e) {
    e->get_distressed();
  }
  /**
   * @brief if entities have collided or detected the collision will hapen
   * in the future in the arena. This event is
   * accepted.
   * @param Pointer to EventTypeEmit e
   */
  virtual void Accept(EventTypeEmit * e) {
    e->get_entity_type();
  }
  // Sensor& operator=(const Sensor& other);
  // Sensor(const Sensor& other);
 private:
  bool activated_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_BASE_H_
