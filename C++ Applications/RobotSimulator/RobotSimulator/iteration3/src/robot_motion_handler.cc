/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"
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
RobotMotionHandler::RobotMotionHandler() :
  adjust_angle_(0),
  name_("Robot"),
  heading_angle_(37),
  speed_(0),
  max_speed_(11),
  angle_delta_(10) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RobotMotionHandler::UpdateVelocity(SensorTouch st, SensorEntityType se,
  SensorProximity sp, SensorDistress sd) {
    if (name_ == "Robot") {
  if (st.get_activated() == 1) {
    // check the speed if after colliding the speed
    // is less than 0, then set current speed is 0
    heading_angle_ = -st.get_angle_of_contact();
    // + adjust_angle_*15;
    // adjust_angle_++;
    // adjust_angle_ = adjust_angle_ % 4;

    // robot or superbot
    if (se.get_entity_type() == 0) {
          speed_ = 5;
    } else if (se.get_entity_type() == 1) {
          speed_ = 5;
    } else if ( se.get_entity_type() == 2 ) {
        // player
        speed_ = 0;
    } else if ( se.get_entity_type() == 3 ) {
        // homebase
        std::cout << "become to superbot, by collided _ " <<
        (se.get_entity_type() == 3) << '\n';
        name_ = "Superbot";
    } else {
        speed_ = 5;
    }
  } else if (sp.get_activated() == 1) {
    // robot
    if ( se.get_entity_type() == 0 ) {
      // frozen robot
      if (sd.get_activated() == 1) {
        heading_angle_ = heading_angle_ + 0;
      } else {
        heading_angle_ = heading_angle_ + 180;
      }
    } else if (se.get_entity_type() == 1) {
        // superbot
        heading_angle_ = heading_angle_ + 180;
    } else if (se.get_entity_type() == 2) {
          // player
        heading_angle_ = heading_angle_ + 0;
    } else if (se.get_entity_type() == 4) {
      // recharge_station_
        heading_angle_ = heading_angle_ + 180;
    } else if (se.get_entity_type() == 6) {
      // obstacles
        heading_angle_ = heading_angle_ + 180;
    } else {
      // homebase
          heading_angle_ = heading_angle_ + 180;
        }
    }
  } else {
    // become to a superbot
    if (st.get_activated() == 1) {
      // check the speed if after colliding the speed
      // is less than 0, then set current speed is 0
      heading_angle_ = -st.get_angle_of_contact();
      // + adjust_angle_ * 15;
      // adjust_angle_++;
      // adjust_angle_ = adjust_angle_ % 4;

      // robot or superbot
      if ( se.get_entity_type() == 0 || se.get_entity_type() == 1 ) {
        std::cout << "Superbot Collided with robto or superbot"<< '\n';
            speed_ = 5;
      }

      } else if (sp.get_activated() == 1) {
        // robot
        if ( se.get_entity_type() == 0 ) {
          // frozen robot
          if (sd.get_activated() == 1) {
            heading_angle_ = heading_angle_ + 0;
          } else {
            heading_angle_ = heading_angle_ + 180;
          }
        } else if (se.get_entity_type() == 1) {
            // superbot
            heading_angle_ = heading_angle_ + 180;
        } else if (se.get_entity_type() == 2) {
              // player
            heading_angle_ = heading_angle_ + 0;
        } else if (se.get_entity_type() == 4) {
          // recharge_station_
            heading_angle_ = heading_angle_ + 180;
        } else if (se.get_entity_type() == 6) {
          // obstacles
            heading_angle_ = heading_angle_ + 180;
        } else {
          // homebase
              heading_angle_ = heading_angle_ + 180;
            }
        }
  }
}

  // void RobotMotionHandler::UpdateSuperbot(SensorEntityType se) {
  //     if ( se.get_entity_type() == 3 ) {
  //         name_ = "Superbot";
  //   }
  // }


NAMESPACE_END(csci3081);
