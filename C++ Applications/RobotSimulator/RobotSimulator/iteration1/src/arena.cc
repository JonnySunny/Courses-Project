/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include "src/arena.h"
#include "src/robot.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"

#define PI 3.14159265
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim), y_dim_(params->y_dim),
  robot_(new Robot(&params->robot)),
  n_robots_(1),
  n_obstacles_(params->n_obstacles),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  robot_->set_heading_angle(37);
  home_base_->set_heading_angle(50);
  entities_.push_back(robot_);
  entities_.push_back(home_base_);
  mobile_entities_.push_back(robot_);
  // home_base_ is mobile now, so it need to be push_back by mobile_entities_
  mobile_entities_.push_back(home_base_);
  entities_.push_back(recharge_station_);


  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::Reset(void) {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

void Arena::AdvanceTime(void) {
  std::cout << "Advancing simulation time by 1 timestep\n";
  UpdateEntitiesTimestep();
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);} /* for(ent..) */

  /*
   * Next, check if the robot has run out of battery
   */
  if (robot_->battery_level() <=0) {
     std::cout << "Lose the game\n";
     assert(0); /* not implemented yet */
  } else if (robot_->battery_level() <= 50) {
		/*
       to represente the battery_level by changing the color
    */
     robot_-> set_color(Color(75, 0, 0, 255));
  } else if (robot_->battery_level() <= 75) {
     robot_-> set_color(Color(150, 0, 0, 255));
  } else if (robot_->battery_level() <= 95) {
     robot_-> set_color(Color(255, 0, 0, 255));
  }



  /*
   * Next, check if the robot has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * robot away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;

  CheckForEntityCollision(robot_, home_base_, &ec, robot_->get_collision_delta());
  if (ec.get_collided()) {
       std::cout << "Win the game\n";
       assert(0);
  }

  CheckForEntityCollision(robot_, recharge_station_,
    &ec, robot_->get_collision_delta());
  if (ec.get_collided()) {
    robot_->set_color(Color(0, 0, 255, 255));
    EventRecharge er;
    robot_->Accept(&er);
  }

  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */
  for (auto ent : mobile_entities_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    assert(ent->is_mobile());
    CheckForEntityOutOfBounds(ent, &ec);

    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.get_collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec, ent->get_collision_delta());
        if (ec.get_collided()) {
          // if(ent->name().at(0)=="R"){
          //   // find the robot from the mobile entities,
          // and have collisions with other entities, not with wall
          //   ent->
          //   ent->
          // }
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */

void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
  EventCollision * event) {
  if (ent->get_pos().x + ent->get_radius() >= x_dim_) {
    // Right Wall
    event->set_collided(true);
    event->set_point_of_contact(Position((int)ent->get_pos().x - 5 , (int)ent->get_pos().y));
    event->set_angle_of_contact(ent->get_heading_angle()-180);

  } else if (ent->get_pos().x- ent->get_radius() <= 0) {
    // Left Wall
    event->set_collided(true);
    event->set_point_of_contact(Position((int)ent->get_pos().x + 5, (int)ent->get_pos().y));
    event->set_angle_of_contact(ent->get_heading_angle()-180);
  } else if (ent->get_pos().y + ent->get_radius() >= y_dim_) {
    // Bottom Wall
    event->set_collided(true);
    event->set_point_of_contact(Position((int)ent->get_pos().x+5, (int)ent->get_pos().y + 5));
    event->set_angle_of_contact(ent->get_heading_angle() );
  } else if (ent->get_pos().y - ent->get_radius() <= 0) {
    // Top Wall
    event->set_collided(true);
    event->set_point_of_contact(Position((int)ent->get_pos().x-5, (int)ent->get_pos().y - 5));
    event->set_angle_of_contact(ent->get_heading_angle());
  } else {
    event->set_collided(false);
  }
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaMobileEntity* const ent1,
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
  if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta) {
    event->set_collided(false);
  } else {
    // Populate the collision event.
    // Collided is true
    // Point of contact is point along perimeter of ent1
    // Angle of contact is angle to that point of contact
    event->set_collided(true);
    /// >>>>>>> FILL THIS IN
    // using atangent funciton to compute the contact angle,
    // required the deltay and deltax
    double deltay = (ent1_y-ent2_y);
    double deltax = (ent1_x-ent2_x);
    double Ang_contact = atan2(deltay, deltax)/PI * 180;
    // Point of cantact
    event->set_point_of_contact(Position((int)ent1_x, (int)ent1_y));
    event->set_angle_of_contact((180 - 2*Ang_contact + ent1->get_heading_angle()));
  }
} /* entities_have_collided() */

void Arena::Accept(__unused EventKeypress * e) {
  // make robot get command from the EventKeypress
  robot_ -> EventCmd(e->get_key_cmd());
}

NAMESPACE_END(csci3081);
