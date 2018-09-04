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
  activated_(0),
  range_(100),
  fov_(100),
  distance_(-1) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorProximity::Accept(EventProximity * e) {
  // Determine if the sensor should be activated or inactivated.
    p1 = e->get_posiiton_of_sensor();
    p2 = e->get_position_of_sensed();
    radius_ = e->get_radius_of_sensed();
    heading_angle_ = e -> get_heading_angle_of_sensor();
    distance_ = SensorProximity::sensor_reading(p1, p2,heading_angle_, radius_ );
}

void SensorProximity::Reset(void) {
  activated_ = 0;
  fov_ = 100;
  range_ = 100;
  distance_ = -1;
} /* reset() */

double SensorProximity::sensor_reading(Position p1, Position p2, double ha, double r){
    double deltaX = p2.x-p1.x;
    double deltaY = p2.y-p1.y;
    double dist = sqrt(pow(deltaX,2) + pow(deltaY,2));
    if (dist > get_range() + r){
    return -1;
    }
    //  triangle is formed from center of r_sensing to the point along the tangents
    //  to r_sensed. The height is dist and the width is r_sensed.radius*2.
    double triangle_theta = abs(((atan(r/dist))*180/3.14));
    double distance_theta = abs(((atan2(deltaY, deltaX))*180/3.14));
    //r_sensing.DrawTriangle(triangle_theta, distance_theta, dist)
    double sensor_lower = ha - (int)(get_fov()/2);
    double sensor_upper = ha + (int)(get_fov()/2);
    double sensed_lower = distance_theta - triangle_theta;
    double sensed_upper = distance_theta + triangle_theta;

    if (in_range( sensor_lower, sensor_upper,
              sensed_lower, sensed_upper )){
    return dist;} else{
    return -1;}

  }
  /*
    reference to proximity.py


  */
  bool SensorProximity::in_range(double sensor_lower, double sensor_upper, double sensed_lower, double sensed_upper){
    if(sensor_lower > sensor_upper){
      double temp = sensor_lower;
      sensor_lower = sensor_upper;
      sensor_upper = temp;
    }
    if(sensed_lower > sensed_upper){
      double temp = sensed_lower;
      sensed_lower = sensed_upper;
      sensed_upper = temp;
    }
    if(sensed_lower >= sensor_lower && sensed_lower <= sensor_upper){
      return true;
    }
    if(sensed_upper >= sensor_lower && sensed_upper <= sensor_upper){
      return true;
    }
    return false;

  }

NAMESPACE_END(csci3081);
