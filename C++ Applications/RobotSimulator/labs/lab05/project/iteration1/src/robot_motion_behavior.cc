/**
 * @file robot_motion_behavior.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_behavior.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RobotMotionBehavior::UpdatePosition(ArenaMobileEntity * const ent,
                                       unsigned int dt) {
  // Save position for debugging purposes
  Position new_pos = ent->pos();
  Position old_pos = ent->pos();

  // Movement is always along the heading_angle (i.e. the hypotenuse)
  new_pos.x += cos(ent->heading_angle()*M_PI/180.0)*ent->speed()*dt;
  new_pos.y += sin(ent->heading_angle()*M_PI/180.0)*ent->speed()*dt;
  ent->pos(new_pos);

  printf(
      "Updated %s kinematics: old_pos=(%d, %d), new_pos=(%d, %d)\n",
      ent->name().c_str(), old_pos.x, old_pos.y, new_pos.x, new_pos.y);
} /* update_position() */

NAMESPACE_END(csci3081);
