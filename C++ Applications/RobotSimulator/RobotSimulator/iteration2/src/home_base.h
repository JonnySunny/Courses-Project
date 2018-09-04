/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_HOME_BASE_H_
#define SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
  #include <string>
  #include <cstdlib>
  #include "src/home_base_params.h"
  #include "src/arena_mobile_entity.h"
  // #include "src/robot_motion_handler.h"
  #include "src/home_base_motion_handler.h"
  #include "src/robot_motion_behavior.h"
  #include "src/sensor_touch.h"
  #include "src/robot_battery.h"
  #include "src/event_recharge.h"
  #include "src/event_collision.h"
  #include "src/sensor_base.h"
  #include "src/event_type_emit.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief  HomeBase class is derived from ArenaMobileEntity class. Its movement in the Arena sometimes will have collision with the wall and immobile entities. That will
  * be handled by mothion handler.
  *
  */
class HomeBase: public ArenaMobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
      heading_angle_(0),
      angle_delta_(params->angle_delta),
      change_angle_(0),
      motion_handler_(),
      motion_behavior_(),
      sensor_touch_()
      {
      motion_handler_.set_heading_angle(270);
      motion_handler_.set_speed(5);
    }


  std::string name(void) const { return "Home Base"; }
  /**
   * @brief Get the HeadingAngle of the entity
   *
   * @return double
   */
  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle(); }
  /**
   * @brief Set the HeadingAngle of the entity
   *
   * @param ha double
   */
  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }
  /**
   * @brief Get the speed of the entity
   *
   * @return double
   */
  double get_speed(void) { return motion_handler_.get_speed(); }
  /**
   * @brief Set the speed of the entity
   *
   * @param  sp double
   */
  void set_speed(double sp) { motion_handler_.set_speed(sp); }
  /**
   * @brief This to update the position, heading_angle, speed, and so on as the unit time passed in.
   * to make entities looks like moving
   * @param Unit dt
   */
  void TimestepUpdate(uint dt) {
    change_angle_ = rand()%1000;
    if ((static_cast<int>(change_angle_) % 250) == 0) {
      set_heading_angle(heading_angle_+change_angle_);
    }
    // Position old_pos = get_pos();
    // Update heading and speed as indicated by touch sensor
    motion_handler_.UpdateVelocity(sensor_touch_);
    // Use velocity and position to update position
    motion_behavior_.UpdatePosition(this, dt);
  } /* TimestepUpdate() */
  /**
   * @brief if entities have collided in the arena. Collision is
   * accepted, because it relavate the heading_angle, and spped of entities after collision
   * @param Pointer to EventCollision e
   */
  void Accept(EventCollision * e) {
    sensor_touch_.Accept(e);
  }
  /**
   * @brief Don't use it, since Homebase doesn't have battary
   */
  void Accept(EventRecharge * e) {
    e-> EmitMessage();
  }
  /**
   * @brief if entities have collided in the arena. Collision is
   * accepted, because it relavate the heading_angle, and spped of entities after collision
   * @param Pointer to EventCollision e
   */
  /**
   * @brief Reset every thing to the original state. i.e position, heading anngle, speed and so on.
   */
  void Reset(void) {
    // reset to the original data
    motion_handler_.Reset();
    sensor_touch_.Reset();
    set_heading_angle(270);
    Position original;
    original.x = 400;
    original.y = 400;
    set_color(Color(255, 0, 0, 255));
    set_pos(original);
  } /* Reset() */
  // void set_name(std::string s) {}

 private:
    double heading_angle_;
    double angle_delta_;
    double change_angle_;
    HomeBaseMotionHandler motion_handler_;
    MotionBehavior motion_behavior_;
    SensorTouch sensor_touch_;
};
NAMESPACE_END(csci3081);


#endif  // SRC_HOME_BASE_H_
