/**
 * @file robot_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include "src/robot_viewer.h"
#include <src/robot.h>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotViewer::RobotViewer()
    : csci3081::GraphicsApp(1024, 768, "Robot Simulation") {

      // Create a menu with 2 buttons for pausing and restarting the simulation.
      /*



      */


  nanogui::FormHelper *gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window =
      gui->addWindow(Eigen::Vector2i(10, 10), "Simulation Controls");
  pause_btn_ =
      gui->addButton("Pause", std::bind(&RobotViewer::OnPauseBtnPressed, this));
  gui->addButton("Restart", std::bind(&RobotViewer::OnRestartBtnPressed, this));

  color_btn_=
gui->addButton("ChangeColor", std::bind(&RobotViewer::OnChangeColorPressed, this));
color.r = 100.0;
color.g = 50.0;
color.b = 75.0;
color.a = 100.0;
  performLayout();
  paused_ = false;

  // Instantiate RobotLand, which holds 2 robots and an obstacle.
  robot_land_ = new RobotLand();

}

RobotViewer::~RobotViewer() { delete robot_land_; }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RobotViewer::UpdateSimulation(double dt) {

  // This is called at each pass through nanogui::mainloop.
  // It sends the time change dt to robot_land_ to advance the simulation.
  if (!paused_) {
    robot_land_->advance_time(dt);
  }
}

// The handlers for the menu buttons ...
/*
    Here is a kind of a loop to change color each time

*/
void RobotViewer::OnChangeColorPressed(){

  if(color.r >= 255 || color.g >= 255 || color.b >= 255 || color.a >= 255){
    color.r = 100.0;
    color.g = 50.0;
    color.b = 75.0;
    color.a = 100.0;
  }
  color.r += 20.0;
  color.g += 20.0;
  color.b += 25.0;
  color.a += 10.0;

  robot_land_ -> change_robot_color(color);
}


void RobotViewer::OnRestartBtnPressed() { robot_land_->set_time(0.0); }

void RobotViewer::OnPauseBtnPressed() {
  paused_ = !paused_;
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}

// The standard mouse and keyboard event callback functions
void RobotViewer::OnMouseMove(int x, int y) {
  std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
}

void RobotViewer::OnLeftMouseDown(int x, int y) {
  std::cout << "Left mouse button DOWN (" << x << ", " << y << ")" << std::endl;
}

void RobotViewer::OnLeftMouseUp(int x, int y) {
  std::cout << "Left mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void RobotViewer::OnRightMouseDown(int x, int y) {
  std::cout << "Right mouse button DOWN (" << x << ", " << y << ")"
            << std::endl;
}

void RobotViewer::OnRightMouseUp(int x, int y) {
  std::cout << "Right mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void RobotViewer::OnKeyDown(const char *c, int modifiers) {
  std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers << std::endl;
}

void RobotViewer::OnKeyUp(const char *c, int modifiers) {
  std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
}

void RobotViewer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
  std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

void RobotViewer::OnSpecialKeyUp(int key, int scancode, int modifiers) {
  std::cout << "Special Key UP key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

// this function requires an active nanovg drawing context (ctx),
// so it should probably only be called from within DrawUsingNanoVG()


/*

    Passing one more variable called color (Robotcolor) to pass the color and control it 

*/
void RobotViewer::DrawRobot(NVGcontext *ctx, int id, double xpos, double ypos,
                            double xvel, double yvel, double rad, Robotcolor color) {
  // translate and rotate all graphics calls that follow so that they are
  // centered
  // at the position and heading for this robot

  // *********
  // IMPORTANT: the nvgSave(ctx) saves the current origin of the coordinate
  // system. When you translate and rotate, it modifies the origin. Any
  // subsequent reference to {x,y} is relative to that origin.
  // The nvgSave needs to be paired with nvgRestore, as that is what returns
  // the origin to its saved position. Notice these can be nested.
  // *********

  // Put the origin of the coordinate system at the center of the robot, and
  // orient the x-axis to align with the velocity (i.e. heading) of the robot.
  nvgSave(ctx);
  nvgTranslate(ctx, xpos, ypos);
  double angle = std::atan2(yvel, xvel);
  nvgRotate(ctx, angle);

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, rad);
  nvgFillColor(ctx, nvgRGBA(color.r, color.g, color.b, color.a));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  std::string text = "Robot " + std::to_string(id);
  nvgText(ctx, 0.0, 10.0, text.c_str(), NULL);
  nvgRestore(ctx);

  nvgRestore(ctx);
}

// this function requires an active nanovg drawing context (ctx),
// so it should probably only be called from with DrawUsingNanoVG()
void RobotViewer::DrawRobotSensors(NVGcontext *ctx, int id, double xpos,
                                   double ypos, double xvel, double yvel,
                                   double rad, double sensor_angle,
                                   double sensor_dist) {
  // translate and rotate all graphics calls that follow so that they are
  // centered at the position and heading for this robot
  nvgSave(ctx);
  nvgTranslate(ctx, xpos, ypos);
  double angle = std::atan2(yvel, xvel);
  nvgRotate(ctx, angle);

  // sensor cone outline
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 100));
  nvgStroke(ctx);
  nvgRestore(ctx);

  // blue for right sensor cone
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(100, 100, 255, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  // yellow for left sensor cone
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(255, 255, 100, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  nvgRestore(ctx);
}

// This function requires an active nanovg drawing context (ctx),
// so it should probably only be called from with DrawUsingNanoVG()
void RobotViewer::DrawObstacle(NVGcontext *ctx, int id, double xpos,
                               double ypos, double rad) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, xpos, ypos, rad);
  nvgFillColor(ctx, nvgRGBA(255, 100, 100, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  std::string text = "Obstacle " + std::to_string(id);
  nvgText(ctx, xpos, ypos, text.c_str(), NULL);
}

void RobotViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  // Draw each obstacle in robot land
  for (int i = 0; i < robot_land_->get_num_obstacles(); i++) {
    double x, y;
    robot_land_->get_obstacle_pos(i, &x, &y);

    DrawObstacle(ctx, i, x, y, robot_land_->get_obstacle_radius(i));
  }

  // Draw each robot in robot land
  for (int i = 0; i < robot_land_->get_num_robots(); i++) {
    double xpos, ypos;
    robot_land_->get_robot_pos(i, &xpos, &ypos);

    double xvel, yvel;
    robot_land_->get_robot_vel(i, &xvel, &yvel);

    DrawRobot(ctx, i, xpos, ypos, xvel, yvel, robot_land_->get_robot_radius(i),robot_land_->get_robot_color(i));
  }

  // Draw the field-of-view for the robot sensors
  // Sensor beams must be drawn last because they are semi transparent
  for (int i = 0; i < robot_land_->get_num_robots(); i++) {
    double xpos, ypos;
    robot_land_->get_robot_pos(i, &xpos, &ypos);

    double xvel, yvel;
    robot_land_->get_robot_vel(i, &xvel, &yvel);

    DrawRobotSensors(ctx, i, xpos, ypos, xvel, yvel,
                     robot_land_->get_robot_radius(i),
                     robot_land_->get_robot_sensor_angle(i),
                     robot_land_->get_robot_sensor_distance(i));
  }
}

NAMESPACE_END(csci3081);
