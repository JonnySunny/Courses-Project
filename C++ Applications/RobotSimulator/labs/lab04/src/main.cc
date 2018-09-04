/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_viewer.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char **argv) {
  csci3081::InitGraphics();

  // RobotViewer is a subclass of GraphicsApp, found in libSimpleGraphics
  // Run() is a function defined in the GraphicsApp class definition.
  // Run() calls nanogui::mainloop().
  csci3081::RobotViewer *app = new csci3081::RobotViewer();
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
