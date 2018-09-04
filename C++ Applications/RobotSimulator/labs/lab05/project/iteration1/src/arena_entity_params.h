/**
 * @file arena_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_ENTITY_PARAMS_H_
#define SRC_ARENA_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct arena_entity_params {
  arena_entity_params(void) : radius(), pos(), color() {}
  double radius;
  Position pos;
  nanogui::Color color;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_ENTITY_PARAMS_H_ */
