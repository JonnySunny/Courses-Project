/**
 * @file home_base_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/home_base_motion_handler.h"
#include <math.h>
#include <stdio.h>
#include "src/position.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

#define PI 3.14159265
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
HomeBaseMotionHandler::HomeBaseMotionHandler() :
  adjust_angle_(0),
  heading_angle_(0),
  speed_(0),
  max_speed_(11),
  angle_delta_(10) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void HomeBaseMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.get_activated() == 1) {
    // check the speed if after colliding the speed
    // is less than 0, then set current speed is 0
    heading_angle_ = -st.get_angle_of_contact();
    // + adjust_angle_*15;
    // adjust_angle_++;
    // adjust_angle_ = adjust_angle_ % 4;
    // }
    // inverse the angle
    // heading_angle_ = -st.get_angle_of_contact();
    }
  }


NAMESPACE_END(csci3081);
