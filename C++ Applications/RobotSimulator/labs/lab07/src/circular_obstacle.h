/**
 * @file circular_obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_CIRCULAR_OBSTACLE_H_
#define SRC_CIRCULAR_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/arena_immobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class that represents are circular, immobile entity within the
 * arena, which we are defining as an "obstacle".
 *
 */
class CircularObstacle: public ArenaImmobileEntity {
 public:
  explicit CircularObstacle(double radius);
  CircularObstacle(double radius, const Position& pos,
                   const nanogui::Color& color);

 /**
 * @brief Get the name of circular obstacle, for use in visualization and
 * debugging
 */
  std::string get_name(void) const override {
    return "Circular Obstacle" + std::to_string(id_);
  }

 private:
  static uint next_id_;

  int id_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_CIRCULAR_OBSTACLE_H_ */
