/**
 * @file circular_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_CIRCULAR_ENTITY_PARAMS_H_
#define SRC_CIRCULAR_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include "src/common.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
/**
 * @brief Define the params for a circular entity in the arena.
 *
 * For now, all entities in the arena are circular.
 */
struct circular_entity_params {
  circular_entity_params(void) : radius(), pos(), color() {}
  double radius;
  Position pos;
  nanogui::Color color;
};

NAMESPACE_END(csci3081);

#endif /* SRC_CIRCULAR_ENTITY_PARAMS_H_ */
