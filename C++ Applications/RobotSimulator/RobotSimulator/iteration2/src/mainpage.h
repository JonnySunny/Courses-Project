#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
/*
"Copyright 2017 <CSCI3081>"
  ! \mainpage CSCI3081 Robot Simulator Project
 *
 *
 * 	Description for this framework:
 *	All of robots have autonomous, intelligent behavior; they can determine their behavior by detecting the different consitions.
 * Users control a player with the arrow keys. The objective of the game is for the player to freeze all robots at the same time before running out of energy.
 * Energy is depleted constantly and is depleted even more when moving or when it bumps into obstacles, but it can renew its energy by going to the charging station.
 * Autonomous robots that use sensors to avoid objects will move around the environment interfering with play.
 * If the user-controlled robot collides with an autonomous robot, it will freeze (i.e. stop moving), but if another autonomous robot collides with a frozen robot,
 * it will move again. A frozen robot will emit a distress call, which when detected by another autonomous robot, allows the moving robot to ignore its proximity
 * sensor and bump into the frozen robot. Furthermore, SuperBots roam the arena and if they collide with the Player, the Player freezes for a fixed period of time.
 * SuperBots become SuperBots by an ordinary Robot colliding with home base. If player runs out of energy before let all robots become freeze, the player lose the game.
 *  reference: iteration2requirement.md
 *
 * 
 *
 */
#endif /* SRC_MAINPAGE_H_ */
