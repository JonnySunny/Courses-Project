/**
 * @file robot_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include "src/robot_battery.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
double RobotBattery::Deplete(__unused Position old_pos,
   __unused Position new_pos, __unused double dt) {
     /* @todo deplete battery by some value based on movement and speed */
     // if the position is not changed ,
     // it just need to deplete just base battery
     if ( old_pos.x == new_pos.x && old_pos.y == new_pos.y ) {
        // handle the negative battery
        if (charge_< dt*kBASE_DEPLETION) {
            charge_ = 0;
        } else {
          charge_ -= dt*kBASE_DEPLETION;}
        } else {
          // compute the linear speed
            double dist = std::sqrt(
            std::pow(old_pos.x - new_pos.x, 2)
            + std::pow(old_pos.y - new_pos.y, 2));
            double linear_vel = dist/dt;
          // handle the negative battery
            if (charge_ < (dt*kBASE_DEPLETION+linear_vel
              * kLINEAR_SCALE_FACTOR)) {
              charge_ = 0;
            } else {
            charge_ -= dt*kBASE_DEPLETION;
            charge_ -= linear_vel * kLINEAR_SCALE_FACTOR;
          }
      }
  return charge_;
  } /* deplete() */

void RobotBattery::Accept(__unused EventCollision * e) {
  /* @todo deplete battery by some value -- arbitrary selected for bumping */
  // handle the negative battery
  if (e->get_collided()) {
    charge_ -= 0.01;
    if (charge_ < 0.01) {
      charge_ = 0;
    } else {
      charge_ -= 0.01;}
    }
}

NAMESPACE_END(csci3081);
