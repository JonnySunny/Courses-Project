/**
 * @file common.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END(name) }

// This should be placed in front of any variable defined but not used to
// satisfy the compiler - otherwise a warning is given.
#define __unused __attribute__((unused))

struct Position {
Position(void) : x(0), y(0) { }
Position(int in_x, int in_y) : x(in_x), y(in_y) { }
  int x;
  int y;
};

#endif   // SRC_COMMON_H_
