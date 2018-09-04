/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
  heading_angle_(0),
  speed_(0),
  max_speed_(5) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  switch (cmd) {
  case COM_TURN_LEFT: break;
  case COM_TURN_RIGHT: break;
  case COM_FORWARD: break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    heading_angle_ = - st.angle_of_contact();
  }
}

NAMESPACE_END(csci3081);
