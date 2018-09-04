/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/position.h"
#include "src/color.h"
#include <fstream>


/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char *argv[]) {
  // Essential call to initiate the graphics window
  csci3081::InitGraphics();

  // Initialize default start values for various arena entities\


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

  argc--;argv++;//Drop the param name

  configfile.open(* argv);
  assert(configfile.is_open()); //make sure file open

  std::string line;
  char command[100];
  int count0 = 0;
  int count1 = 0;
  while(getline(configfile,line)){
    if(line[0]=='#') continue; //line comments
    sscanf(line.c_str(),"%s ",command);
    std::string cmd = command;

    if(cmd == "obstacle") {
      float x,y,rod;
      int r,g,b,a;
      sscanf(line.c_str(), "obstacle %f %f %f %d %d %d %d", &x, &y, &rod, &r, &g, &b, &a);
      std::cout << "o"<< x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
      aparams.obstacles[count0].radius = rod;
      aparams.obstacles[count0].pos = {x,y};
      aparams.obstacles[count0].color = csci3081::Color(r,g,b,a);
      count0++;
    } else if(cmd == "player") {
      float x,y,rod,bmc,ad;
      int cd,r,g,b,a;
      sscanf(line.c_str(), "player %f %f %f %f %f %d %d %d %d %d", &x, &y, &rod, &bmc, &ad, &cd, &r, &g, &b, &a);
      std::cout << "p" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
      pparams.pos = {x,y};
      pparams.radius = rod;
      pparams.battery_max_charge = bmc;
      pparams.angle_delta = ad;
      pparams.collision_delta = cd;
      pparams.color = csci3081::Color(r,g,b,a);
      aparams.player = pparams;
    } else if(cmd == "recharge_station") {
      float x,y,rod;
      int r,g,b,a;
      sscanf(line.c_str(), "recharge_station %f %f %f %d %d %d %d", &x, &y, &rod, &r, &g, &b, &a);
      std::cout << "r" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
      aparams.recharge_station.radius = rod;
      aparams.recharge_station.pos = {x,y};
      aparams.recharge_station.color = csci3081::Color(r,g,b,a);
    } else if (cmd == "homebase") {
      float x,y,rod,ad;
      int r,g,b,a;
      sscanf(line.c_str(), "homebase %f %f %f %f %d %d %d %d", &x, &y, &rod, &ad, &r, &g, &b, &a);
      std::cout << "h" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
      aparams.home_base.pos = {x,y};
      aparams.home_base.radius = rod;
      aparams.home_base.angle_delta = ad;
      aparams.home_base.color = csci3081::Color(r,g,b,a);
      // aparams.home_base = hparams;
    }  else if(cmd == "robot") {
        float x,y,rod,ad;
        int r,g,b,a;
        sscanf(line.c_str(), "robot %f %f %f %f %d %d %d %d", &x, &y, &rod, &ad, &r, &g, &b, &a);
        std::cout << "robot" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
        aparams.robots[count1].angle_delta=ad;
        aparams.robots[count1].radius = rod;
        aparams.robots[count1].pos = {x,y};
        aparams.robots[count1].color = csci3081::Color(r,g,b,a);
        count1++;
      }
    //  else if (cmd == "robot1") {
    //   float x,y,rod,ad;
    //   int r,g,b,a;
    //   sscanf(line.c_str(), "robot1 %f %f %f %f %d %d %d %d", &x, &y, &rod, &ad, &r, &g, &b, &a);
    //   std::cout << "robot" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
    //   rparam1.pos = {x,y};
    //   rparam1.radius = rod;
    //   rparam1.angle_delta = ad;
    //   rparam1.color = csci3081::Color(r,g,b,a);
    //   aparams.robot1 = rparam1;
    // }
    // else if (cmd == "robot2"){
    //   float x,y,rod,ad;
    //   int r,g,b,a;
    //   sscanf(line.c_str(), "robot2 %f %f %f %f %d %d %d %d", &x, &y, &rod, &ad, &r, &g, &b, &a);
    //   std::cout << "robot" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
    //   rparam2.pos = {x,y};
    //   rparam2.radius = rod;
    //   rparam2.angle_delta = ad;
    //   rparam2.color = csci3081::Color(r,g,b,a);
    //   aparams.robot2 = rparam2;
    // }  else if (cmd == "robot3"){
    //   float x,y,rod,ad;
    //   int r,g,b,a;
    //   sscanf(line.c_str(), "robot3 %f %f %f %f %d %d %d %d", &x, &y, &rod, &ad, &r, &g, &b, &a);
    //   std::cout << "robot" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
    //   rparam3.pos = {x,y};
    //   rparam3.radius = rod;
    //   rparam3.angle_delta = ad;
    //   rparam3.color = csci3081::Color(r,g,b,a);
    //   aparams.robot3 = rparam3;
    // } else if (cmd == "robot4"){
    //   float x,y,rod,ad;
    //   int r,g,b,a;
    //   sscanf(line.c_str(), "robot4 %f %f %f %f %d %d %d %d", &x, &y, &rod, &ad, &r, &g, &b, &a);
    //   std::cout << "robot" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
    //   rparam4.pos = {x,y};
    //   rparam4.radius = rod;
    //   rparam4.angle_delta = ad;
    //   rparam4.color = csci3081::Color(r,g,b,a);
    //   aparams.robot4 = rparam4;
    // }  else if (cmd == "robot5"){
    //   float x,y,rod,ad;
    //   int r,g,b,a;
    //   sscanf(line.c_str(), "robot5 %f %f %f %f %d %d %d %d", &x, &y, &rod, &ad, &r, &g, &b, &a);
    //   std::cout << "robot" << x << " " << y << " " << rod << " " << r << " " << g << " "<< b<<" "<<a<<" " << '\n';
    //   rparam5.pos = {x,y};
    //   rparam5.radius = rod;
    //   rparam5.angle_delta = ad;
    //   rparam5.color = csci3081::Color(r,g,b,a);
    //   aparams.robot5 = rparam5;
    // }

  }
    aparams.n_robots = 5;
    aparams.n_obstacles = 5;
    aparams.x_dim = 1024;
    aparams.y_dim = 768;


  //
  //
  // rparams.battery_max_charge = 100.0;
  // rparams.angle_delta = 10;
  // rparams.collision_delta = 1;
  // rparams.radius = 20.0;
  // rparams.pos = {500, 500};
  // rparams.color = csci3081::Color(0, 0, 255, 255); /* blue */
  //
  //
  // aparams.player = rparams;
  //
  // aparams.recharge_station.radius = 20.0;
  // aparams.recharge_station.pos = {500, 300};
  // aparams.recharge_station.color =
  // csci3081::Color(0, 128, 128, 255); /* green */
  //
  // aparams.home_base.radius = 20.0;
  // aparams.home_base.pos = {400, 400};
  // aparams.home_base.color = csci3081::Color(255, 0, 0, 255); /* red */
  //
  // aparams.obstacles[0].radius = 30.0;
  // aparams.obstacles[0].pos = {200, 200};
  // aparams.obstacles[0].color = {255, 255, 255, 255};
  //
  // aparams.obstacles[1].radius = 30.0;
  // aparams.obstacles[1].pos = {300, 300};
  // aparams.obstacles[1].color = {255, 255, 255, 255};
  //
  // aparams.obstacles[2].radius = 30.0;
  // aparams.obstacles[2].pos = {500, 700};
  // aparams.obstacles[2].color = {255, 255, 255, 255};
  //
  // aparams.obstacles[3].radius = 30.0;
  // aparams.obstacles[3].pos = {550, 600};
  // aparams.obstacles[3].color = {255, 255, 255, 255};
  //
  // aparams.obstacles[4].radius = 30.0;
  // aparams.obstacles[4].pos = {100, 600};
  // aparams.obstacles[4].color = {255, 255, 255, 255};
  //
  //
  // aparams.n_obstacles = 5;
  // aparams.x_dim = 1024;
  // aparams.y_dim = 768;


  // Start up the graphics (which creates the arena).
  // Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
    new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
