/**
 * @file robot_land.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include "robot.h"
#include <iostream>
 /*******************************************************************************
  * Member Functions
  ******************************************************************************/

Robot::Robot(){
  x_pos=500.0;
  y_pos=500.0;
  x_vel = 100.0;
  y_vel = 100.0;
  color.r = 255.0;
  color.g = 255.0;
  color.b = 100.0;
  color.a = 0.0;
  radius = 50.0;
}

Robot::Robot(double inx_pos,double iny_pos,double inx_vel, double iny_vel, double inradius, Robotcolor incolor){
  color.r = incolor.r;
  color.g = incolor.g;
  color.b = incolor.b;
  color.a = incolor.a;
  x_pos = inx_pos;
  y_pos = iny_pos;
  x_vel = inx_vel;
  y_vel = iny_vel;
  radius = inradius;
}

//get size
void Robot::set_robot_radius(double initradius){
  radius = initradius;
}

void Robot::set_robot_color(Robotcolor incolor){
  color.r = incolor.r;
  color.g = incolor.g;
  color.b = incolor.b;
  color.a = incolor.a;
}

/*
Follow the same pattern in robot_land
*/

void Robot::set_robot_xpos(double inx_pos){
  x_pos= circle_x(inx_pos);
}
void Robot::set_robot_ypos(double iny_pos){
  y_pos =  circle_y(iny_pos);
}
//
void Robot::set_robot_xvel(double inx_vel){
  x_vel = circle_x(inx_vel);
}
void Robot::set_robot_yvel(double iny_vel){
  y_vel = circle_y(iny_vel);
}

Robotcolor Robot::get_robot_color(){
  return color;
}
double Robot::get_robot_radius(){
  return radius;
}

double Robot::get_robot_xpos(){
  return x_pos;
}
double Robot::get_robot_ypos(){
  return y_pos;
}

//
double Robot::get_robot_xvel(){
  return x_vel;
}
double Robot::get_robot_yvel(){
  return y_vel;
}
