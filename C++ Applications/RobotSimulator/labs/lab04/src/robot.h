/**
 * @file robot.h
 *
 *
 */
#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <cmath>
/*******************************************************************************
 * Namespaces
 ******************************************************************************/

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

 struct Robotcolor{
       double r;
       double g;
       double b;
       double a;
 };

class Robot{


private:
  double x_pos;
  double y_pos;
  double x_vel;
  double y_vel;
  Robotcolor color;
  double radius;

  double circle_x(double t) { return 512 + 200.0 * cos(t); }
  double circle_y(double t) { return 350 + 200.0 * sin(t); }


public:
  Robot();
  /*

  This Constructor ommited the color variable, do it later.

  */
  Robot(double inx_pos,double iny_pos, double inx_vel,double iny_vel,double inradius, Robotcolor color);

  //get size
  void set_robot_radius(double initradius);
  void set_robot_color(Robotcolor incolor);

  void set_robot_xpos(double inx_pos);
  void set_robot_ypos(double iny_pos);
  void set_robot_xvel(double inx_vel);
  void set_robot_yvel(double iny_vel);


  Robotcolor get_robot_color();
  double get_robot_radius();
  double get_robot_xpos();
  double get_robot_ypos();
  double get_robot_xvel();
  double get_robot_yvel();



};

#endif
