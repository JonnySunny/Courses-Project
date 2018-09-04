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
  id_(-1),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  battery_(params->battery_max_charge),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_() {
  motion_handler_.heading_angle(270);
  motion_handler_.speed(5);
  id_ = next_id_++;
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();

  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);

  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);

  // Deplete battery as appropriate given distance and speed of movement
  battery_.Deplete(old_pos, get_pos(), dt);
} /* TimestepUpdate() */

void Robot::Accept(__unused const EventRecharge * const e) {
  battery_.EventRecharge();
}

void Robot::Accept(const EventCollision * const e) {
  sensor_touch_.Accept(e);
}

void Robot::EventCmd(enum event_commands cmd) {
  motion_handler_.AcceptCommand(cmd);
} /* event_cmd() */

void Robot::Reset(void) {
  battery_.Reset();
  motion_handler_.Reset();
  sensor_touch_.Reset();
} /* Reset() */

void Robot::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
