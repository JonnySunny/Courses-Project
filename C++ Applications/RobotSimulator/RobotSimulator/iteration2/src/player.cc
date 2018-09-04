/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Player::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Player::Player(const struct player_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  battery_(params->battery_max_charge),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  freeze_time_(0),
  id_(-1) {
  motion_handler_.set_angle_delta(angle_delta_);
  motion_handler_.set_heading_angle(270);
  motion_handler_.set_speed(5);
  id_ = next_id_++;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Player::TimestepUpdate(uint dt) {
  if (motion_handler_.get_speed() == 0) {
    freeze_time_++;
  }
  if (freeze_time_ % 100 == 0) {
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  // Use velocity and position to update position
  }
  motion_behavior_.UpdatePosition(this, dt);
  Position old_pos = get_pos();
  // Deplete battery as appropriate given distance and speed of movement
  battery_.Deplete(old_pos, get_pos(), dt);
} /* TimestepUpdate() */

void Player::Accept(__unused EventRecharge * e) {
  battery_.EventRecharge();
}

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Player::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
  battery_.Accept(e);
}

// User input commands to change heading or speed
void Player::EventCmd(enum event_commands cmd) {
  motion_handler_.AcceptCommand(cmd);
} /* event_cmd() */

void Player::Reset(void) {
  // reset to original data
  battery_.Reset();
  motion_handler_.Reset();
  sensor_touch_.Reset();
  set_heading_angle(37);
  Position original;
  original.x = 500;
  original.y = 500;
  set_pos(original);
  set_color(Color(0, 0, 255, 255));
} /* Reset() */

void Player::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
