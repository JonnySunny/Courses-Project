/**
 * @file robot_land.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "robot_land.h"



/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// Hard coded for 2 robots moving in circular patterns
int RobotLand::get_num_robots(void) { return 2; }

// Hard coded for now...
// Once the robot class is added, this getter should call the robot getters
bool RobotLand::get_robot_pos(int id, double *x_pos, double *y_pos) {
  if (id == 0) {
    robot.set_robot_xpos(sim_time_);
    robot.set_robot_ypos(sim_time_);
    *x_pos = robot.get_robot_xpos();
    *y_pos = robot.get_robot_ypos();

    return true;
  } else if (id == 1) {
    // make this robot slower
    double t = 0.75 * sim_time_;
    robot2.set_robot_xpos(t);
    robot2.set_robot_ypos(t);
    *x_pos = robot2.get_robot_xpos();
    *y_pos = robot2.get_robot_ypos();
    return true;
  } else {
    return false;
  }
}

// Hard coded for now...
// Once the robot class is added, this getter should call the robot getters
// Notice the use of "id" -- how will you handle this in your robot class??
bool RobotLand::get_robot_vel(int id, double *x_vel, double *y_vel) {
  double xnow, ynow, xprev, yprev;
  double delta = 0.1;
  if (id == 0) {
    robot.set_robot_xvel(sim_time_);
    robot.set_robot_yvel(sim_time_);

    xnow = robot.get_robot_xvel();
    ynow = robot.get_robot_yvel();

    robot.set_robot_xvel(sim_time_ - delta);
    robot.set_robot_yvel(sim_time_ - delta);
    xprev = robot.get_robot_xvel();
    yprev = robot.get_robot_yvel();


    *x_vel = xnow - xprev;
    *y_vel = ynow - yprev;

    return true;
  } else if (id == 1) {
    // make this robot slower
    double t = 0.75 * sim_time_;

    robot.set_robot_xvel(t);
    robot.set_robot_yvel(t);

    xnow = robot.get_robot_xvel();
    ynow = robot.get_robot_yvel();

    robot.set_robot_xvel(t - delta);
    robot.set_robot_yvel(t - delta);
    xprev = robot.get_robot_xvel();
    yprev = robot.get_robot_yvel();

    *x_vel = xnow - xprev;
    *y_vel = ynow - yprev;
    return true;
  } else {
    return false;
  }
}

Robotcolor RobotLand::get_robot_color(int id){
  if (id == 1 ) return robot2.get_robot_color();
  else  return robot.get_robot_color();
}

// Hard coded for now...
double RobotLand::get_robot_radius(int id) {
  if (id == 1 ){
      robot2.set_robot_radius(75);
      return robot2.get_robot_radius();}
  else return robot.get_robot_radius();}

// Hard coded for now...  in radians
double RobotLand::get_robot_sensor_angle(int id) { return 2.0; }

// Hard coded for now...
double RobotLand::get_robot_sensor_distance(int id) {
  return 3.0 * get_robot_radius(id);
}

// Hard coded for now...
int RobotLand::get_num_obstacles() { return 1; }

// Hard coded for now...
bool RobotLand::get_obstacle_pos(int id, double *x_pos, double *y_pos) {
  if (id == 0) {
    *x_pos = 200;
    *y_pos = 300;
    return true;
  }
  return false;
}

// Hard coded for now...
double RobotLand::get_obstacle_radius(int id) { return 75; }
