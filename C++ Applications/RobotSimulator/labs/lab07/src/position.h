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
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A simple representation of a position of an entity within the arena.
 */
class Position {
 public:
  Position(void) : x_(0), y_(0) {}
  Position(int in_x, int in_y) : x_(in_x), y_(in_y) { }

  int x(void) const { return x_; }
  int y(void) const { return y_; }
  void x(double x) { x_ = x; }
  void y(double y) { y_ = y; }

  Position& operator=(const Position& other) {
    this->x_ = other.x_;
    this->y_ = other.y_;
    return *this;
  }

 private:
  int x_;
  int y_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_POSITION_H_ */
