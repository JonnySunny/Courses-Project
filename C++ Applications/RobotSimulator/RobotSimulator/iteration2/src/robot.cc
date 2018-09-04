/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Robot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot(const struct robot_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  name_("Robot"),
  heading_angle_(params->heading_angle),
  angle_delta_(params->angle_delta),
  battery_(params->battery_max_charge),
  motion_handler_(),
  motion_behavior_(),
  sensor_distress_(),
  sensor_touch_(),
  sensor_entity_type_(),
  sensor_proximity_(),
  state_proximity_(0),
  state_distress_(0),
  id_(-1) {
  motion_handler_.set_angle_delta(angle_delta_);
  motion_handler_.set_heading_angle(heading_angle_);
  motion_handler_.set_speed(5);
  motion_handler_.set_name(name_);
  id_ = next_id_++;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(uint dt) {
  // Position old_pos = get_pos();
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_, sensor_entity_type_,
    sensor_proximity_, sensor_distress_);
  // motion_handler_.UpdateSuperbot(sensor_entity_type_);
  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
  // Deplete battery as appropriate given distance and speed of movement
  // battery_.Deplete(old_pos, get_pos(), dt);
} /* TimestepUpdate() */

void Robot::Accept(__unused EventRecharge * e) {
  battery_.EventRecharge();
}

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Robot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
  battery_.Accept(e);
}

// // User input commands to change heading or speed
// void Robot::EventCmd(enum event_commands cmd) {
//   motion_handler_.AcceptCommand(cmd);
// } /* event_cmd() */

void Robot::Accept(EventTypeEmit * e) {
  sensor_entity_type_.Accept(e);
}

void Robot::Accept(EventProximity * e) {
  sensor_proximity_.Accept(e);
}

void Robot::Accept(EventDistressCall * e) {
  sensor_distress_.Accept(e);
}

void Robot::Reset(void) {
  // reset to original data
  name_ = "Robot";
  battery_.Reset();
  motion_handler_.Reset();
  sensor_touch_.Reset();
  sensor_entity_type_.Reset();
  sensor_proximity_.Reset();
  sensor_distress_.Reset();
  if (id_ == 0) {
    set_heading_angle(75);
    set_pos(Position(300, 100));
    set_color(Color(0, 0, 255, 255));
  } else if (id_ == 1) {
    set_heading_angle(15);
    set_pos(Position(500, 150));
    set_color(Color(0, 0, 255, 255));
  } else if (id_ == 2) {
    set_heading_angle(25);
    set_pos(Position(500, 200));
    set_color(Color(0, 0, 255, 255));
  } else if (id_ == 3) {
    set_heading_angle(45);
    set_pos(Position(500, 250));
    set_color(Color(0, 0, 255, 255));
  } else if (id_ == 4) {
    set_heading_angle(65);
    set_pos(Position(500, 350));
    set_color(Color(0, 0, 255, 255));
  }
} /* Reset() */

void Robot::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
