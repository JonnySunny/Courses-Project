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
// #include "src/robot.h"
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
  // robot_(new Robot(&params->robot)),
  // robot1_(new Robot(&params->robot1)),
  // robot2_(new Robot(&params->robot2)),
  // robot3_(new Robot(&params->robot3)),
  // robot4_(new Robot(&params->robot4)),
  // robot5_(new Robot(&params->robot5)),
  n_robots_(params->n_robots),
  n_obstacles_(params->n_obstacles),
  freeze_time_(0),
  player_(new Player(&params->player)),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_(),
  robots_() {
  player_->set_heading_angle(37);
  home_base_->set_heading_angle(50);
  entities_.push_back(player_);
  entities_.push_back(home_base_);
  // entities_.push_back(robot1_);
  // entities_.push_back(robot2_);
  // entities_.push_back(robot3_);
  // entities_.push_back(robot4_);
  // entities_.push_back(robot5_);
  mobile_entities_.push_back(player_);
  // home_base_ is mobile now, so it need to be push_back by mobile_entities_
  // mobile_entities_.push_back(robot1_);
  // mobile_entities_.push_back(robot2_);
  // mobile_entities_.push_back(robot3_);
  // mobile_entities_.push_back(robot4_);
  // mobile_entities_.push_back(robot5_);
  mobile_entities_.push_back(home_base_);
  entities_.push_back(recharge_station_);


  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */

  for (size_t i = 0; i < n_robots_; ++i) {
    Robot* r = new Robot(
      &params->robots[i]);
      registerRobot(r);
      entities_.push_back(r);
      // mobile_entities_.push_back(r);
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
void Arena::registerRobot(Robot *observer) {
  robots_.push_back(observer);
  }

  void Arena::removeRobot(Robot *observer) {
// find the observer
auto iterator = std::find(robots_.begin(), robots_.end(), observer);
if (iterator != robots_.end()) {  //  observer found
robots_.erase(iterator);  //  remove the observer
  }
}

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

std::vector<Robot*> Arena::robots(void) {
  std::vector<Robot*> res;
  for (auto ent : entities_) {
    Robot* r = dynamic_cast<Robot*>(ent);
    if (r) {
      res.push_back(r);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

void Arena::AdvanceTime(void) {
  // std::cout << "Advancing simulation time by 1 timestep\n";
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
  unsigned int n_superbot_ = 0;
  for (auto robot : robots_) {
    if (robot->name().substr(0, 5) == "Super") {
      n_superbot_++;
      if (n_superbot_ == robots_.size()) {
       std::cout << "Lose the game, all robots are superbots\n";
       assert(0); /* not implemented yet */
      }
    }
  }
  unsigned int n_robot_ = 0;
  for (auto robot : robots_) {
    if (robot->name().substr(0, 5) == "Robot" && robot->get_speed() == 0) {
      n_robot_++;
    }
  }
  if (n_robot_ == robots_.size() - n_superbot_) {
    std::cout << "Win the game, all robots are frezon\n";
    assert(0); /* not implemented yet */
  }





  if (player_->battery_level() <=0) {
     std::cout << "Lose the game, battery_level is 0 \n";
     assert(0); /* not implemented yet */
  } else if (player_->battery_level() <= 50) {
		/*
       to represente the battery_level by changing the color
    */
     player_-> set_color(Color(75, 0, 0, 255));
  } else if (player_->battery_level() <= 75) {
     player_-> set_color(Color(150, 0, 0, 255));
  } else if (player_->battery_level() <= 95) {
     player_-> set_color(Color(255, 0, 0, 255));
  }



  /*
   * Next, check if the robot has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * robot away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;
  EventProximity ep;
  EventTypeEmit et;
  EventDistressCall ed;
  ed.set_distressed(false);
  et.set_entity_type(None);
  // ec.set_x_dim(x_dim_);
  // ec.set_y_dim(y_dim_);
  CheckForEntityCollision(player_, home_base_, &ec,
    player_->get_collision_delta());
  if (ec.get_collided()) {
      //  std::cout << "Win the game\n";
      //  assert(0);
  }

  CheckForEntityCollision(player_, recharge_station_,
    &ec, player_->get_collision_delta());
  if (ec.get_collided()) {
    player_->set_color(Color(0, 0, 255, 255));
    EventRecharge er;
    player_->Accept(&er);
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
    // ec.set_ent1(ent);
    CheckForEntityOutOfBounds(ent, &ec);
    et.set_entity_type(None);
    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.get_collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        //  cheack robot with homeabse
        CheckForEntityCollision(ent, entities_[i], &ec,
          ent->get_collision_delta());
        if (ec.get_collided()) {
          break;
          }
        }
      } /* for(i..) */
        ent->Accept(&ec);
    }
    for (auto robot : robots_) {
      // Check if it is out of bounds. If so, use that as point of contact.
      assert(robot->is_mobile());
      // ec.set_ent1(ent);
      CheckForEntityOutOfBounds(robot, &ec);
      et.set_entity_type(None);
      // If not at wall, check if colliding with any other entities (not itself)
      if (!ec.get_collided()) {
        for (size_t i = 0; i < entities_.size(); ++i) {
          if (entities_[i] == robot) {
            continue;
          }
          //  cheack robot with homeabse
          CheckForEntityCollision(robot, entities_[i], &ec,
            robot->get_collision_delta());
          if (ec.get_collided()) {
            et.set_entity_type(None);
            if (entities_[i]->name().substr(0, 5) == "Home ") {
              // robot->set_color(Color(155, 155, 255, 255));
              et.set_entity_type(kHomeBase);
              robot->Accept(&et);
              robot->Accept(&ed);
              break;
            }
            if (entities_[i]->name().substr(0, 5) == "Robot") {
              et.set_entity_type(kRobot);
              robot->Accept(&et);
              robot->Accept(&ed);
              break;
            }
            if (entities_[i]->name().substr(0, 5) == "Playe") {
              if (robot->name().substr(0, 5) == "Super") {
                player_->set_speed(0);
              } else {
              ed.set_distressed(true);
              std::cout << "Distress call is activated_ "<< '\n';
              et.set_entity_type(kPlayer);
              robot->Accept(&et);
              robot->Accept(&ed);
              }
              break;
            }
            if (entities_[i]->name().substr(0, 5) == "Super") {
              et.set_entity_type(kSuperBot);
              robot->Accept(&et);
              robot->Accept(&ed);
              break;
            } else {
              robot->Accept(&et);
              robot->Accept(&ed);
              break;
            }

              break;

          } else {
              et.set_entity_type(None);
              ep.set_position_of_sensor(robot->get_pos());
              ep.set_position_of_sensed(entities_[i]->get_pos());
              ep.set_heading_angle_of_sensor(robot->get_heading_angle());
              ep.set_radius_of_sensed(entities_[i]->get_radius());
              robot->Accept(&ep);
              // entities_[i]
              // std::cout << entities_[i]<< '\n';
              if (robot->get_sensor_proximity_state() == 1) {
              // event proximity happened
                  if (entities_[i]->name().substr(0, 5) == "Playe") {
                    et.set_entity_type(kPlayer);
                    robot->Accept(&et);
                    robot->Accept(&ed);
                    break;
                  }
                  if (entities_[i]->name().substr(0, 5) == "Recha") {
                    et.set_entity_type(kRechargeStation);
                    robot->Accept(&et);
                    robot->Accept(&ed);
                    break;
                  }
                  if (entities_[i]->name().substr(0, 5) == "Obsta") {
                    et.set_entity_type(kObstacle);
                    robot->Accept(&et);
                    robot->Accept(&ed);
                    break;
                  }
                  if (entities_[i]->name().substr(0, 5) == "Home ") {
                    // robot->set_color(Color(155, 155, 255, 255));
                    et.set_entity_type(None);
                    robot->Accept(&et);
                    robot->Accept(&ed);
                    break;
                  }
                  if (entities_[i]->name().substr(0, 5) == "Robot") {
                    if (((reinterpret_cast<Robot*>(entities_[i]))
                    ->get_sensor_distress_state() == 1)) {
                      ed.set_distressed(true);
                    } else {
                      ed.set_distressed(false); }
                    et.set_entity_type(kRobot);
                    robot->Accept(&ed);
                    robot->Accept(&et);
                    break;
                  }
                  if (entities_[i]->name().substr(0, 5) == "Super") {
                    et.set_entity_type(kSuperBot);
                    robot->Accept(&et);
                    robot->Accept(&ed);
                    break;
                  }
               break;
            }
          }
        }
      }
      robot->Accept(&ec);
    }
  }


  void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity *const ent,
                                        EventCollision *const event) {
    if (ent->get_pos().x + ent->get_radius() >= x_dim_) {
      // Right Wall
      event->set_collided(true);
      event->set_point_of_contact(Position(x_dim_, ent->get_pos().y));
      event->set_angle_of_contact(ent->get_heading_angle() - 180);
    } else if (ent->get_pos().x - ent->get_radius() <= 0) {
      // Left Wall
      event->set_collided(true);
      event->set_point_of_contact(Position(0, ent->get_pos().y));
      event->set_angle_of_contact(ent->get_heading_angle() - 180);
    } else if (ent->get_pos().y + ent->get_radius() >= y_dim_) {
      // Bottom Wall
      event->set_collided(true);
      event->set_point_of_contact(Position(ent->get_pos().x, y_dim_));
      event->set_angle_of_contact(ent->get_heading_angle());
    } else if (ent->get_pos().y - ent->get_radius() <= 0) {
      // Top Wall
      event->set_collided(true);
      event->set_point_of_contact(Position(0, y_dim_));
      event->set_angle_of_contact(ent->get_heading_angle());
    } else {
      event->set_collided(false);
    }
  } /* entity_out_of_bounds() */

  void Arena::CheckForEntityCollision(const ArenaMobileEntity *const ent1,
                                      const ArenaEntity *const ent2,
                                      EventCollision *const event,
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
      // ref: https://stackoverflow.com/a/1736741
      event->set_collided(true);

      double angle = std::asin(std::abs(ent2_x - ent1_x) / dist);

      if ((ent2_x - ent1_x) > 0) {
        if ((ent2_y - ent1_y) > 0) {
          // lower right
          event->set_point_of_contact(
              {
                  ent1_x + std::sin(angle) * ent1->get_radius(),
                  ent1_y + std::cos(angle) * ent1->get_radius()
              });
          angle = M_PI_2 - angle;
        } else if ((ent2_y - ent1_y) < 0) {
          // upper right
          event->set_point_of_contact(
              {
                  ent1_x + std::sin(angle) * ent1->get_radius(),
                  ent1_y - std::cos(angle) * ent1->get_radius()
              });
          angle += (3 * M_PI_2);
        } else {  // if ((ent2_y - ent1_y) == 0)
          // 0 or 360 deg
          event->set_point_of_contact(
              {
                  ent1_x + ent1->get_radius(),
                  ent1_y
              });
          angle = 0;
        }
      } else if ((ent2_x - ent1_x) < 0)  {
        if ((ent2_y - ent1_y) > 0) {
          // lower left
          event->set_point_of_contact(
              {
                  ent1_x - std::sin(angle) * ent1->get_radius(),
                  ent1_y + std::cos(angle) * ent1->get_radius()
              });
          angle += M_PI_2;
        } else if ((ent2_y - ent1_y) < 0) {
          // upper left
          event->set_point_of_contact(
              {
                  ent1_x - std::sin(angle) * ent1->get_radius(),
                  ent1_y - std::cos(angle) * ent1->get_radius()
              });
          angle = (M_PI_2 * 2) + (M_PI_2 - angle);
        } else {  // if ((ent2_y - ent1_y) == 0)
          // 180 deg
          event->set_point_of_contact(
              {
                  ent1_x - ent1->get_radius(),
                  ent1_y
              });
          angle = M_PI;
        }
      } else {  // if ((ent2_x - ent1_x) == 0)
        if ((ent2_y - ent1_y) > 0) {
          // 90 deg
          event->set_point_of_contact(
              {
                  ent1_x,
                  ent1_y + ent1->get_radius()
              });
          angle = M_PI_2;
        } else if ((ent2_y - ent1_y) < 0) {
          // 270 deg
          event->set_point_of_contact(
              {
                  ent1_x,
                  ent1_y - ent1->get_radius()
              });
          angle = (3 * M_PI_2);
        } else {  // if ((ent2_y - ent1_y) == 0)
          // completely overlap, which is theoretically impossible...
          std::cerr << ent1->name() << " is in complete overlap with "
                    << ent2->name() << ".\n";
          assert(false);
        }
      }

      event->set_angle_of_contact((M_PI - angle) / M_PI * 180);
    }
  }



void Arena::Accept(__unused EventKeypress * e) {
  // make robot get command from the EventKeypress
  if ( player_->get_freeze_time() % 100 == 0 ) {
  player_ -> EventCmd(e->get_key_cmd());
  }
}

NAMESPACE_END(csci3081);
