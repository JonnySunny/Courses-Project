/**
 * @file sensor_distress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_distress.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorDistress::SensorDistress() :
  activated_(0),
  range_(40)
{}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorDistress::Accept(EventDistressCall * e) {
  // Determine if the sensor should be activated or inactivated.
  if (e -> get_distressed()) {
    activated_ = 1;
  } else {
    activated_ = 0;
  }
}

void SensorDistress::Reset(void) {
  activated_ = 0;
  range_ = 40;
} /* reset() */

NAMESPACE_END(csci3081);
