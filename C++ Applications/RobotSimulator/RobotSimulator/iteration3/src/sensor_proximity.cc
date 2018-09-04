/**
 * @file sensor_proximity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <limits>
#include "src/sensor_proximity.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorProximity::SensorProximity() :
  range_(40),
  fov_(40),
  distance_(-1),
  p1_(Position(0, 0)),
  p2_(Position(0, 0)),
  heading_angle_(0),
  radius_(0),
  sensed_(NULL),
  activated_(0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorProximity::Accept(EventProximity * e) {
  // Determine if the sensor should be activated or inactivated.
    p1_ = e->get_position_of_sensor();
    p2_ = e->get_position_of_sensed();
    radius_ = e->get_radius_of_sensed();
    heading_angle_ = e -> get_heading_angle_of_sensor();
    distance_ = SensorProximity::sensor_reading(p1_,
      p2_, heading_angle_, radius_);
    if (distance_ > -1) {
      activated_ = 1;
    } else {
      activated_ = 0;
    }
}

void SensorProximity::Reset(void) {
  // activated_ = 0;
  fov_ = 40;
  range_ = 40;
  distance_ = -1;
} /* reset() */

double SensorProximity::sensor_reading(Position p1,
  Position p2, double ha, double r) {
    double deltaX = p2.x-p1.x;
    double deltaY = p2.y-p1.y;
    double dist = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    if (dist > get_range() + r) {
    return -1;
    }
    //  triangle is formed from center of r_sensing to the point along the
    //  tangents
    //  to r_sensed. The height is dist and the width is r_sensed.radius*2.
    double triangle_theta = Positive(((atan(r/dist))*180/3.14));
    double distance_theta = Positive(((atan2(deltaY, deltaX))*180/3.14));
    // r_sensing.DrawTriangle(triangle_theta, distance_theta, dist)
    double sensor_lower = ha - static_cast<int>(get_fov()/2);
    double sensor_upper = ha + static_cast<int>(get_fov()/2);
    double sensed_lower = distance_theta - triangle_theta;
    double sensed_upper = distance_theta + triangle_theta;

    if (in_range(Positive(sensor_lower), Positive(sensor_upper),
              sensed_lower, sensed_upper)) {
    return dist; } else {
    return -1;}
  }
  /*
    reference to proximity.py
  */
  bool SensorProximity::in_range(double sensor_lower, double sensor_upper,
    double sensed_lower, double sensed_upper) {
    if (sensor_lower > sensor_upper) {
      double temp = sensor_lower;
      sensor_lower = sensor_upper;
      sensor_upper = temp;
    }
    if (sensed_lower > sensed_upper) {
      double temp = sensed_lower;
      sensed_lower = sensed_upper;
      sensed_upper = temp;
    }
    if (sensed_lower >= sensor_lower && sensed_lower <= sensor_upper ||
      sensed_lower >= sensor_lower + 360
      && sensed_lower <= sensor_upper + 360 ||
      sensed_lower >= sensor_lower - 360
      && sensed_lower <= sensor_upper - 360) {
      return true;
    }
    if (sensed_upper >= sensor_lower && sensed_upper <= sensor_upper ||
       sensed_upper >= sensor_lower + 360
       && sensed_upper <= sensor_upper + 360 ||
        sensed_upper >= sensor_lower - 360
        && sensed_upper <= sensor_upper - 360) {
      return true;
    }
    return false;
  }

NAMESPACE_END(csci3081);
