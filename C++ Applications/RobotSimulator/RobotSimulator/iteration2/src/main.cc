/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <fstream>
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/position.h"
#include "src/color.h"



/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
/*
  @bug
  1.Restart Robots don't have a original heading angle.
  2.hard code for color and position
  3. When have collide with homebase, just change
    the color and the name to represent
    it becomes to superbot
  4.sometimes collision happen between robot and
    player, but robot didn't freeze
  5. Some not needed function For example, set_name for the immobilentity...
  6. Some wrong iformation don't have time to fix,
    for example For example, Player has "Robotbattary"
    which could be confused, and so on.
  7.lose game in terminal means the battery is 0
  8.Player collided with robot, is not very perfect. sometimes work, but sometime don't work
  9. proximixiy Sensot doesn't work well, sometimes, it will detect the the entity

*/
int main(int argc, char *argv[]) {
  // Essential call to initiate the graphics window
  csci3081::InitGraphics();
  // Initialize default start values for various arena entities
  csci3081::player_params pparams;
  csci3081::robot_params rparam;
  // csci3081::robot_params rparam1;
  // csci3081::robot_params rparam2;
  // csci3081::robot_params rparam3;
  // csci3081::robot_params rparam4;
  // csci3081::robot_params rparam5;
  csci3081::arena_params aparams;
  csci3081::home_base_params hparams;

  std::ifstream configfile;

  argc = 2;
  argv[0] = "iteration2";
  argv[1] = "config.txt";

  argc--; argv++;  // Drop the param name

  configfile.open(* argv);
  assert(configfile.is_open());  // make sure file open

  std::string line;
  char command[100];
  int count0 = 0;
  int count1 = 0;
  while (getline(configfile, line)) {
    if (line[0] == '#') continue;  // line comments
    sscanf(line.c_str(), "%s ", command);
    std::string cmd = command;

    if (cmd == "obstacle") {
      float x, y, rod;
      int r, g, b, a;
      sscanf(line.c_str(), "obstacle %f %f %f %d %d %d %d",
      &x, &y, &rod, &r, &g, &b, &a);
      std::cout << "o"<< x << " " << y << " " << rod
      << " " << r << " " << g << " "<< b <<" "<< a <<" " << '\n';
      aparams.obstacles[count0].radius = rod;
      aparams.obstacles[count0].pos = {x, y};
      aparams.obstacles[count0].color = csci3081::Color(r, g, b, a);
      count0++;
    } else if (cmd == "player") {
      float x, y, rod, bmc, ad;
      int cd, r, g, b, a;
      sscanf(line.c_str(), "player %f %f %f %f %f %d %d %d %d %d",
      &x, &y, &rod, &bmc, &ad, &cd, &r, &g, &b, &a);
      std::cout << "p" << x << " " << y << " " << rod <<
      " " << r << " " << g << " "<< b <<" "<< a <<" " << '\n';
      pparams.pos = {x, y};
      pparams.radius = rod;
      pparams.battery_max_charge = bmc;
      pparams.angle_delta = ad;
      pparams.collision_delta = cd;
      pparams.color = csci3081::Color(r, g, b, a);
      aparams.player = pparams;
    } else if (cmd == "recharge_station") {
      float x, y, rod;
      int r, g, b, a;
      sscanf(line.c_str(), "recharge_station %f %f %f %d %d %d %d",
      &x, &y, &rod, &r, &g, &b, &a);
      std::cout << "r" << x << " " << y << " " << rod << " "
       << r << " " << g << " "<< b <<" "<< a <<" " << '\n';
      aparams.recharge_station.radius = rod;
      aparams.recharge_station.pos = {x, y};
      aparams.recharge_station.color = csci3081::Color(r, g, b, a);
    } else if (cmd == "homebase") {
      float x, y, rod, ad;
      int r, g, b, a;
      sscanf(line.c_str(), "homebase %f %f %f %f %d %d %d %d",
      &x, &y, &rod, &ad, &r, &g, &b, &a);
      std::cout << "h" << x << " " << y << " " << rod << " "
      << r << " " << g << " "<< b <<" "<< a <<" " << '\n';
      aparams.home_base.pos = {x, y};
      aparams.home_base.radius = rod;
      aparams.home_base.angle_delta = ad;
      aparams.home_base.color = csci3081::Color(r, g, b, a);
      // aparams.home_base = hparams;
    }  else if (cmd == "robot") {
        float x, y, rod, ad;
        int r, g, b, a, ha;
        sscanf(line.c_str(), "robot %f %f %f %f %d %d %d %d %d",
        &x, &y, &rod, &ad, &r, &g, &b, &a, &ha);
        std::cout << "robot" << x << " " << y << " " << rod <<
        " " << r << " " << g << " "<< b <<" "<< ha <<" " << '\n';
        aparams.robots[count1].angle_delta = ad;
        aparams.robots[count1].radius = rod;
        aparams.robots[count1].pos = {x, y};
        aparams.robots[count1].color = csci3081::Color(r, g, b, a);
        aparams.robots[count1].heading_angle = ha;
        count1++;
      }
  }
    aparams.n_robots = 5;
    aparams.n_obstacles = 5;
    aparams.x_dim = 1024;
    aparams.y_dim = 768;

  // Start up the graphics (which creates the arena).
  // Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
    new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
