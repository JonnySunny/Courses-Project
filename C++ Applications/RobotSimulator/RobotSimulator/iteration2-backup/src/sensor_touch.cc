/**
 * @file sensor_touch.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_touch.h"
#include "src/arena_entity.h"
#define PI 3.14159265
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorTouch::SensorTouch() :
  activated_(0),
  point_of_contact_(0, 0),
  angle_of_contact_(0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 void SensorTouch::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
   EventCollision * event, double x_dim_, double y_dim_) {
   if (ent->get_pos().x + ent->get_radius() >= x_dim_-3) {
     // Right Wall
     event->set_collided(true);
     event->set_point_of_contact(Position((int)ent->get_pos().x, (int)ent->get_pos().y));
     event->set_angle_of_contact(ent->get_heading_angle()-180);

   } else if (ent->get_pos().x - ent->get_radius() <= 3) {
     // Left Wall
     event->set_collided(true);
     event->set_point_of_contact(Position((int)ent->get_pos().x, (int)ent->get_pos().y));
     event->set_angle_of_contact(ent->get_heading_angle()-180);
   } else if (ent->get_pos().y + ent->get_radius() >= y_dim_-3) {
     // Bottom Wall
     event->set_collided(true);
     event->set_point_of_contact(Position((int)ent->get_pos().x, (int)ent->get_pos().y ));
     event->set_angle_of_contact(ent->get_heading_angle() );
   } else if (ent->get_pos().y - ent->get_radius() <= 3) {
     // Top Wall
     event->set_collided(true);
     event->set_point_of_contact(Position((int)ent->get_pos().x, (int)ent->get_pos().y));
     event->set_angle_of_contact(ent->get_heading_angle());
   } else {
     event->set_collided(false);
   }
 } /* entity_out_of_bounds() */


 void SensorTouch::CheckForEntityCollision(const ArenaEntity* const ent1,
   const ArenaEntity* const ent2,
  EventCollision * event,
   double collision_delta) {
   /* Note: this assumes circular entities */
   double ent1_x = ent1->get_pos().x;
   double ent1_y = ent1->get_pos().y;
   double ent2_x = ent2->get_pos().x;
   double ent2_y = ent2->get_pos().y;
   double dist = std::sqrt(
     std::pow(ent2_x - ent1_x, 2) + std::pow(ent2_y - ent1_y, 2));
   if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta + 1) {
     event->set_collided(false);
   } else {
     // Populate the collision event.
     // Collided is true
     // Point of contact is point along perimeter of ent1
     // Angle of contact is angle to that point of contact

     /// >>>>>>> FILL THIS IN
     // using atangent funciton to compute the contact angle,
     // required the deltay and deltax
     double deltay = (ent1_y-ent2_y);
     double deltax = (ent1_x-ent2_x);
     double Ang_contact = atan2(deltay, deltax)/PI * 180;
     // Point of cantact
     event->set_point_of_contact(Position((int)ent1_x, (int)ent1_y));
     event->set_angle_of_contact((180 - 2*Ang_contact + ((ArenaMobileEntity*)(ent1))->get_heading_angle()));
     event->set_collided(true);
   }
 } /* entities_have_collided() */


void SensorTouch::Accept(EventCollision * e) {
  // Determine if the sensor should be activated or inactivated.
  // CheckForEntityOutOfBounds((ArenaMobileEntity*)(e->get_ent1()),
  //   e,
  //   e->get_x_dim(), e->get_y_dim());
    // if (e->get_collided())
    //   {
    //    activated_ = 1;
    //    point_of_contact_ = e->get_point_of_contact();
    //    angle_of_contact_ = e->get_angle_of_contact();
    //  } else {
  // e -> set_collided(false);
  // CheckForEntityCollision(e->get_ent1(),
  //   e->get_ent2(),
  //   e,
  //   ((ArenaMobileEntity*)(e->get_ent1()))->get_collision_delta());
    if (e->get_collided()) {
    activated_ = 1;
    point_of_contact_ = e->get_point_of_contact();
    angle_of_contact_ = e->get_angle_of_contact();
    } else {
      activated_ = 0;
    }
  }


void SensorTouch::Reset(void) {
  activated_ = 0;
  point_of_contact_=Position(0,0);
  angle_of_contact_ = 0;
} /* reset() */

NAMESPACE_END(csci3081);
