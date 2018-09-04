/**
 * @file position.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "common.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A simplified representation of position.
 */
 struct Position {
 Position(void) : x(0), y(0) { }
 Position(double in_x, double in_y) : x(in_x), y(in_y) { }
   double x;
   double y;
 };

NAMESPACE_END(csci3081);

#endif /* SRC_POSITION_H_ */
