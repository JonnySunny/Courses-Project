/**
 * @file Circular_obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/circular_obstacle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint CircularObstacle::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
CircularObstacle::CircularObstacle(double radius, const Position& pos,
                                   const nanogui::Color& color) :
    ArenaImmobileEntity(radius, pos, color),
    id_(-1) {
  id_ = next_id_++;
}

NAMESPACE_END(csci3081);
