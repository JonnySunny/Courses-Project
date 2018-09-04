/**
 * @file arena_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 *
 */

#ifndef SRC_ARENA_PARAMS_H_
#define SRC_ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_params.h"
#include "src/home_base_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
#define MAX_OBSTACLES 8
/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
 * @brief Define the parameter for the arena.
 *
 * This includes the arena geometry as well as the parameters for \c ALL
 * entities within the arena.
 */
struct arena_params {
  arena_params(void) : robot(), recharge_station(), home_base(),
                       obstacles(), n_obstacles(), x_dim(), y_dim() {}

  struct robot_params robot;
  struct circular_entity_params recharge_station;
  struct home_base_params home_base;
  struct circular_entity_params obstacles[MAX_OBSTACLES];
  size_t n_obstacles;
  uint x_dim;
  uint y_dim;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_PARAMS_H_ */
