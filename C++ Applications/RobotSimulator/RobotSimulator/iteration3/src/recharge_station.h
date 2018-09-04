/**
 * @file recharge_station.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_RECHARGE_STATION_H_
#define SRC_RECHARGE_STATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/obstacle.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A derived class from Obstacle.
  * Basiclly also get in the way of the robot, but will recharge the battery of robot
  *
  */
class RechargeStation: public Obstacle {
 public:
  RechargeStation(double radius, const Position& pos,
                  const Color& color) :
      Obstacle(radius, pos, color) {}
  std::string name(void) const {
    return "Recharge Station";
  }
};

NAMESPACE_END(csci3081);

#endif /* SRC_RECHARGE_STATION_H_ */
