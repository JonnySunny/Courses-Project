/**
 * @file robot_arena.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_H_
#define SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include "src/event_keypress.h"
#include "src/event_collision.h"
#include "src/robot.h"
#include "src/home_base.h"
#include "src/recharge_station.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * @brief The main class for the simulation of a 2D world with many robots running
 * around.
 *
 * RobotViewer or Tests call \ref set_time and \ref advance_time to control the
 * simulation and use the get*() functions to read out the current state of the
 * simulation (i.e., the current positions and orientations of robots and
 * obstacles).
 *
 *  For now, RobotArena is hard coded to run a simulation of two robots running
 *  around in a circle.  You can see their sensors, but they don't yet respond
 *  to each other or to obstacles.
 */
class Arena {
 public:
  explicit Arena(const struct arena_params * const params);
  ~Arena(void);

  /**
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by.
   */
  void AdvanceTime(unsigned int dt);

  /**
  * @brief Handle the key press passed along by the viewer.
  *
  * @param[in] an event holding the key press.
  *
  */
  void Accept(EventKeypress * e);

  // Reset all in the arena
  void Reset(void);

  /*
   * @brief Get the # of robots in the arena.
   */
  unsigned int n_robots(void) { return n_robots_; }

  /*
   * @brief Get # of obstacles in the arena.
   */
  unsigned int n_obstacles(void) { return n_obstacles_; }

  /**
   * @brief Get a list of all obstacles (i.e. non-mobile entities in the arena).
   */
  std::vector<class Obstacle*> obstacles(void);

  /**
   * @brief Get the list of all mobile entities in the arena.
   */
  std::vector<class ArenaMobileEntity*> mobile_entities(void)
    { return mobile_entities_; }

  Robot* robot(void) const { return robot_; }
  HomeBase* home_base(void) const { return home_base_; }
  RechargeStation* recharge_station(void) const { return recharge_station_; }


 private:
  /**
   * @brief Determine if two entities have collided in the arena. Collision is
   * defined as the difference between the extents of the two entities being less
   * than a run-time parameter.
   *
   * @param ent1 Entity #1.
   * @param ent2 Entity #2.
   * @param pointer to a collision event
   *
   * Collision Event is populated appropriately.
   */
  void CheckForEntityCollision(const class ArenaEntity* const ent1,
    const class ArenaEntity* const ent2,
    EventCollision * ec,
    double collision_delta);

  /**
   * @brief Determine if a particular entity is gone out of the boundaries of
   * the simulation.
   *
   * @param ent The entity to check.
   * @param pointer to a collision event.
   *
   * Collision event is populated appropriately.
   */
  void CheckForEntityOutOfBounds(const class ArenaMobileEntity* const ent,
    EventCollision * ec);

  /**
   * @brief Update all entities for a single timestep
   */
  void UpdateEntitiesTimestep(void);

  // Under certain circumstance, the compiler requires that the copy
  // constructor is not defined. This is deleting the default copy const.
  Arena& operator=(const Arena& other) = delete;
  Arena(const Arena& other) = delete;

  // Dimensions of graphics window inside which robots must operate
  double x_dim_;
  double y_dim_;
  unsigned int n_robots_;
  unsigned int n_obstacles_;

  // Entities populating the arena
  Robot* robot_;
  RechargeStation * recharge_station_;
  HomeBase * home_base_;
  std::vector<class ArenaEntity*> entities_;
  std::vector<class ArenaMobileEntity*> mobile_entities_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
