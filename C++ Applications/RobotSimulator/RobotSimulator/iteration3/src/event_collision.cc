/**
 * @file event_collision.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_collision.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructor
 ******************************************************************************/
EventCollision::EventCollision() :
  x_(0.0),
  y_(0.0),
  ent1_(NULL),
  ent2_(NULL),
  collided_(false),
  point_of_contact_(0.0, 0.0),
  angle_of_contact_(0.0) {
  // speed_(0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void EventCollision::EmitMessage(void) {
  printf("Collision event at point %f %f. Angle %f",
  point_of_contact_.x, point_of_contact_.y, angle_of_contact_);
} /* EmitMessage() */

NAMESPACE_END(csci3081);
