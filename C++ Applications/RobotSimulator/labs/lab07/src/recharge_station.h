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
#include "src/circular_obstacle.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A class representing a recharge station within the arena that is used
  * to recharge robot batteries.
  */
class RechargeStation: public CircularObstacle {
 public:
  RechargeStation(double radius, const Position& pos,
                  const nanogui::Color& color) :
      CircularObstacle(radius, pos, color) {}
  std::string get_name(void) const override {
    return "Recharge Station";
  }
};

NAMESPACE_END(csci3081);

#endif /* SRC_RECHARGE_STATION_H_ */
