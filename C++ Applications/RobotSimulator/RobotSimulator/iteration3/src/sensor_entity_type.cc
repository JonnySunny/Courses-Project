/**
 * @file sensor_entity_type.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_entity_type.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorEntityType::SensorEntityType() :
  type_(None) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorEntityType::Accept(EventTypeEmit * e) {
  // Determine if the sensor should be activated or inactivated.
    type_ = e->get_entity_type();
}

void SensorEntityType::Reset(void) {
  type_ = None;
} /* reset() */

NAMESPACE_END(csci3081);
