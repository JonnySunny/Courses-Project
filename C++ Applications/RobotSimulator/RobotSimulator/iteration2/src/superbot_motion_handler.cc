// /**
//  * @file robot_motion_handler.cc
//  *
//  * @copyright 2017 3081 Staff, All rights reserved.
//  */
//
// /*******************************************************************************
//  * Includes
//  ******************************************************************************/
// #include "src/superbot_motion_handler.h"
// #include <math.h>
// #include <stdio.h>
// #include "src/position.h"
// /*******************************************************************************
//  * Namespaces
//  ******************************************************************************/
// NAMESPACE_BEGIN(csci3081);
//
// #define PI 3.14159265
// /*******************************************************************************
//  * Constructors/Destructor
//  ******************************************************************************/
// SuperbotMotionHandler::SuperbotMotionHandler() :
//   MotionHandler(),
//   name_("SuperRobot"),
//   heading_angle_(0),
//   speed_(0),
//   max_speed_(11),
//   angle_delta_(10) {
// }
//
// /*******************************************************************************
//  * Member Functions
//  ******************************************************************************/
// // void SuperbotMotionHandler::AcceptCommand(enum event_commands cmd) {
// //   switch (cmd) {
// //   case COM_TURN_LEFT:
// //   // counter-clocwise
// //     HeadingAngleDec(angle_delta_);
// //     break;
// //   case COM_TURN_RIGHT:
// //   // clocwise
// //     HeadingAngleInc(angle_delta_);
// //     break;
// //   case COM_SPEED_UP:
// //   // check if the speed over the max_speed_
// //     if (get_speed() < (get_max_speed()-0.5)) {
// //       speed_ = get_speed()+0.5;
// //       set_speed(speed_);
// //     } else {
// //   // set max_speed
// //       set_speed(get_max_speed());
// //     }
// //     break;
// //   case COM_SLOW_DOWN:
// //   // check if the speed below than 0
// //     if (get_speed() > 0.5) {
// //       speed_ = get_speed()-0.5;
// //       set_speed(speed_);
// //     } else {
// //   // set speed is 0
// //         set_speed(0); }
// //     break;
// //   default:
// //     std::cerr << "FATAL: bad actuator command" << std::endl;
// //     assert(0);
// //   } /* switch() */
// // } /* accept_command() */
//
// void SuperbotMotionHandler::UpdateVelocity(SensorTouch st,
//   SensorEntityType se) {
//   if (st.get_activated() == 1) {
//     // check the speed if after colliding the speed
//     // is less than 0, then set current speed is 0
//     speed_ = speed_ * 0.9;
//     if ( speed_ < 0 ) {
//       speed_ = 0;
//     }
//     // inverse the angle
//     heading_angle_ = -st.get_angle_of_contact();
//     if ( se.get_entity_type() == 3 ) {
//         name_ = "Superbot";
//   }
//     }
//   }
//
//   // void RobotMotionHandler::UpdateSuperbot(SensorEntityType se) {
//   //     if ( se.get_entity_type() == 3 ) {
//   //         name_ = "Superbot";
//   //   }
//   // }
//
//
// NAMESPACE_END(csci3081);
