/**
 * @file robot_land.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_LAND_H_
#define SRC_ROBOT_LAND_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <src/robot.h>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the simulation of a 2D world with many robots running
 * around.
 *
 * RobotViewer or Tests call \ref set_time and \ref advance_time to control the
 * simulation and use the get*() functions to read out the current state of the
 * simulation (i.e., the current positions and orientations of robots and
 * obstacles).
 *
 *  For now, RobotLand is hard coded to run a simulation of two robots running
 *  around in a circle.  You can see their sensors, but they don't yet respond
 *  to each other or to obstacles.
 */
class RobotLand {
 public:
  RobotLand(void) { sim_time_ = 0.0; }

  /**
   * @brief Set the simulation time for \ref RobotLand.
   *
   * This function will be used mainly for testing purposes, as time flows in a
   * steady forward direction in general simulation.
   *
   * @param[in] t The new simulation time.
   */
  void set_time(double t) {
    sim_time_ = t;
    std::cout << "Setting simulation time to " << sim_time_ << std::endl;
  }

  /**
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by.
   */

  // Once the robot class is created, this should call a robot method to
  // advance its position and set the velocity based on dt
  void advance_time(double dt) {
    sim_time_ += dt;
    std::cout << "Advancing simulation time to " << sim_time_ << std::endl;
  }
  /*
    change the robot color via passing this structor
  */

void change_robot_color(Robotcolor icolor){
    robot2.set_robot_color(icolor);
    robot.set_robot_color(icolor);
}

  /**
   * @brief Get the current simulation time.
   */
  double get_current_time(void) { return sim_time_; }

  /*
   * @brief Get the current # of robots in the arena. Currently a stub.
   *
   * @todo: Actually implement this.
   */
  int get_num_robots(void);

  /**
   * @brief Get the current position of the specified robot. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @param[in] id The ID of the robot.
   * @param[out] x_pos The X position of the robot.
   * @param[out] y_pos The Y position of the robot.
   *
   * @return @todo: What does this mean?
   */
  bool get_robot_pos(int id, double *x_pos, double *y_pos);

  /**
   * @brief Get the current velocity of the specified robot. Currently a stub.
   *
   * @todo Actually implement this.
   *
   * @param[in] id The ID of the robot.
   * @param[out] x_vel The X component of velocity.
   * @param[out] y_vel The Y component of velocity.
   *
   * @return @todo what does this mean?
   */
  bool get_robot_vel(int id, double *x_vel, double *y_vel);




/*

  Return Robotcolor structor

*/
  Robotcolor get_robot_color(int id);
  /**
   * @brief Get the radius of the specified robot. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @param[in] id The ID of the robot.
   *
   * @return The robot's radius.
   */
  double get_robot_radius(int id);

  /**
   * @brief Get the angle of the specified robots sensor, in radians. Currently
   * a stub.
   *
   * @todo: Actually implement this.
   *
   * @param id The ID of the robot.
   *
   * @return The sensor angle in radians,
   */
  double get_robot_sensor_angle(int id);

  /**
   * @brief Get the distance of a specified robot's sensor. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @param[in] id The ID of the robot.
   *
   * @return The sensor distance.
   */
  double get_robot_sensor_distance(int id);

  /**
   * @brief Get the # of obstacles currently in RobotLand. Currently a stub.
   *
   * @todo: Actually implement this.
   *
   * @return The # of obstacles.
   */
  int get_num_obstacles(void);

  /**
   * @brief Get the position of the specified obstacle. Currently a stub.
   *sw
   * @todo: Actually implement this.
   *
   * @param[in] id The ID of the obstacle.
   * @param[out] x_pos The X component of the position.
   * @param[out] y_pos The Y component of the position.
   *
   * @return @todo What does this mean?
   */
  bool get_obstacle_pos(int id, double *x_pos, double *y_pos);

  /**
   * @brief Get the radius of the specified obstacle.
   *
   * @param[in] id The ID of the obstacle.
   *
   * @return The obstacle's radius.
   */
  double get_obstacle_radius(int id);

 private:
  // Hard coding these robots to move in a circle
  // double circle_x(double t) { return 512 + 200.0 * cos(t); }
  // double circle_y(double t) { return 350 + 200.0 * sin(t); }
  double circle_x(double t) { return 512 + 200.0 * cos(t); }
  double circle_y(double t) { return 350 + 200.0 * sin(t); }
  double sim_time_;
  Robotcolor color;


  Robot  robot;
  Robot  robot2;
};

#endif  // SRC_ROBOT_LAND_H_
