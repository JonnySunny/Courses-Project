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
#include "src/player_params.h"
#include "src/home_base_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
#define MAX_OBSTACLES 8
#define MAX_ROBOTS 8
/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
  * @brief  Parameters are used in arena
  *
  */
struct arena_params {
 public:
    arena_params(void) :
    robot(), player(), recharge_station(),
    home_base(), obstacles(), robots(), n_robots(0), n_obstacles(0),
    x_dim(0), y_dim(0) {}
  struct robot_params robot;
  struct player_params player;
  struct arena_entity_params recharge_station;
  struct home_base_params home_base;
  struct arena_entity_params obstacles[MAX_OBSTACLES];
  struct robot_params robots[MAX_ROBOTS];
  size_t n_robots;
  size_t n_obstacles;
  uint x_dim;
  uint y_dim;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_PARAMS_H_
