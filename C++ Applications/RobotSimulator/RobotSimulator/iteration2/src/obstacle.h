/**
 * @file obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_OBSTACLE_H_
#define SRC_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/arena_immobile_entity.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A derived class from immobile arena entity.
  * Basiclly get in the way of the robot, and after robot collides with it, robot slow down the speed and deplete battery
  *
  */
class Obstacle: public ArenaImmobileEntity {
 public:
  Obstacle(double radius, const Position& pos,
                   const Color& color);

  std::string name(void) const {
    return "Obstacle" + std::to_string(id_);
  }

 private:
  static uint next_id_;

  int id_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_OBSTACLE_H_ */
