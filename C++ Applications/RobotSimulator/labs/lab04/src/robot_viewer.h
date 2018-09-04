/**
 * @file robot_viewer.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_VIEWER_H_
#define SRC_ROBOT_VIEWER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <simple_graphics/graphics_app.h>
#include "src/robot_land.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 *  @brief An application that uses the cs3081 SimpleGraphics library to open up
 *  a window that includes a few buttons for controlling the simulation and can
 *  be used to draw circles and other computer graphics.
 *
 *  After constructing a new RobotViewer, call Run() to start and run the
 *  application.  Run() will not return until the application window is closed.
 *  Make sure that you call cs3081::InitGraphics() before creating the
 *  RobotViewer app.  Example:
 *
 *  ```
 *  int main(int argc, char **argv) {
 *      cs3081::InitGraphics();
 *      RobotViewer *app = new RobotViewer();
 *      app->Run();
 *      cs3081::ShutdownGraphics();
 *      return 0;
 *  }
 *  ```
 *
 *  While the window is open \ref UpdateSimulation() will be called repeatedly,
 *  once per frame.  Fill this in to update your simulation or perform any other
 *  processing that should happen over time as the simulation progresses.
 *
 *  Fill in the On*() methods as desired to respond to user input events.
 *
 *  Fill in the Draw*() methods to draw graphics to the screen using
 *  either the nanovg library or raw OpenGL.
 */
class RobotViewer : public csci3081::GraphicsApp {
 public:
  RobotViewer();
  ~RobotViewer();

  void UpdateSimulation(double dt);
  /*
      Everytime user preses this button will change the color on the robots

  */
  void OnChangeColorPressed();

  /**
   * @brief Handle the user pressing the restart button on the GUI.
   */


  void OnRestartBtnPressed();

  /**
   * @brief Handle the user pressing the pause button on the GUI.
   */
  void OnPauseBtnPressed();

  /**
   * @brief Called each time the mouse moves on the screen within the GUI
   * window.
   *
   * Origin is at the lower left of the window.
   *
   * @param[in] x X position of the cursor.
   * @param[in] y Y position of the cursor.
   */
  void OnMouseMove(int x, int y);

  /**
   * @brief Called each time the left mouse button is clicked.
   *
   * Origin is at the lower left of the window.
   *
   * @param[in] x The X position of the click.
   * @param[in] y The Y position of the click.
   */
  void OnLeftMouseDown(int x, int y);

  /**
   * @brief Called each time the left mouse button is released.
   *
   * Origin is at the lower left of the window.
   *
   * @param[in] x The X position of the release.
   * @param[in] y The Y position of the release.
   */
  void OnLeftMouseUp(int x, int y);

  /**
   * @brief Called each time the right mouse button is clicked.
   *
   * Origin is at the lower left of the window.
   *
   * @param[in] x The X position of the click.
   * @param[in] y The Y position of the click.
   */

  void OnRightMouseDown(int x, int y);

  /**
   * @brief Called each time the right mouse button is released.
   *
   * Origin is at the lower left of the window.
   *
   * @param[in] x The X position of the release.
   * @param[in] y The Y position of the release.
   */
  void OnRightMouseUp(int x, int y);

  /**
   * @brief Called each time a character key is pressed.
   *
   * @param[in] c Character representing a key that was pressed.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnKeyDown(const char *c, int modifiers);

  /**
   * @brief Called each time a character key is released.
   *
   * @param[in] c Character representing a key that was released.
   * @param[in] modifiers Any modifier keys that were held with the key.
   */
  void OnKeyUp(const char *c, int modifiers);

  /**
   * @brief Called each time a special (non-alphabetic) key is pressed.
   *
   * @param[in] key The key that was pressed.
   * @param[in] scancode The scancode corresponding to the key.
   * @param[in] modifiers Any modifiers that were also pressed.
   */
  void OnSpecialKeyDown(int key, int scancode, int modifiers);

  /**
   * @brief Called each time a special (non-alphabetic) key is released.
   *
   * @param[in] key The key that was released.
   * @param[in] scancode The scancode corresponding to the key.
   * @param[in] modifiers Any modifiers that were also pressed.
   */
  void OnSpecialKeyUp(int key, int scancode, int modifiers);

  /**
   * @brief Draw the arena with all robots, obstacles using nanogui.
   *
   * @param[in] ctx Context for nanogui.
   */
  void DrawUsingNanoVG(NVGcontext *ctx);

  /**
   * @brief Draw using OpenGL. This callback had to be defined, but we are doing
   * all drawing with nanovg in this application, so it is empty.
   */
  void DrawUsingOpenGL(void) {}

 private:
  /**
   * @brief Draw a robot using nanogui.
   *
   * @param[in] ctx The nanogui context.
   * @param[in] id The ID of the robot.
   * @param[in] xpos The X position of the robot.
   * @param[in] ypos The Y position of the robot.
   * @param[in] xvel The X velocity of the robot.
   * @param[in] yvel The Y velocity of the robot.
   * @param[in] rad The radius of the robot.
   */
  void DrawRobot(NVGcontext *ctx, int id, double xpos, double ypos, double xvel,
                 double yvel, double rad, Robotcolor color);

  /**
   * @brief Draw the sensors from a robot using nanogui.
   *
   * @param[in] ctx The nanogui context.
   * @param[in] id The ID of the robot.
   * @param[in] xpos The X position of the robot.
   * @param[in] ypos The Y position of the robot.
   * @param[in] xvel The X velocity of the robot.
   * @param[in] yvel The Y velocity of the robot.
   * @param[in] rad The radius of the robot.
   * @param[in] sensor_angle The angle of the robot's sensor.
   * @param[in] sensor_dist The range of the sensor.
   */
  void DrawRobotSensors(NVGcontext *ctx, int id, double xpos, double ypos,
                        double xvel, double yvel, double rad,
                        double sensor_angle, double sensor_dist);

  /**
   * @brief Draw an obostacle in the arena using nanogui.
   *
   * @param[in] ctx The nanogui context.
   * @param[in] id The ID of the obstacle.
   * @param[in] xpos The X position of the obstacle.
   * @param[in] ypos The Y position of the obstacle.
   * @param[in] rad The radius of the obstacle.
   */
  void DrawObstacle(NVGcontext *ctx, int id, double xpos, double ypos,
                    double rad);

  RobotLand *robot_land_;
  bool paused_;
  bool color_control;
  Robotcolor color;
  nanogui::Button *pause_btn_;
  nanogui::Button *color_btn_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ROBOT_VIEWER_H_ */
