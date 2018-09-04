/**
 * @file arena_mobile_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_PARAMS_H_
#define SRC_ARENA_MOBILE_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct arena_mobile_entity_params : public arena_entity_params {
  arena_mobile_entity_params(void) : arena_entity_params(),
                               collision_delta() {}

  double collision_delta;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_MOBILE_ENTITY_PARAMS_H_ */
