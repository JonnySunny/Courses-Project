/**
 * @file entity_type.h
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 */

#ifndef SRC_ENTITY_TYPE_H_
#define SRC_ENTITY_TYPE_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
enum entity_type {
  kRobot,  // 0
  kSuperBot,  // 1
  kPlayer,  // 2
  kHomeBase,  // 3
  kRechargeStation,  // 4
  kWall,  // 5
  kObstacle,  // 6
  None  // 7
};
NAMESPACE_END(csci3081);

#endif  // SRC_ENTITY_TYPE_H_
