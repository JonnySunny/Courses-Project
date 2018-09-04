/**
 * @file arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_ENTITY_H_
#define SRC_ARENA_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include "src/common.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A base class representing an entity within the arena. All entities
 * within the arena know how to :
 *
 * 1. Update themselves each timestep (i.e. in accordance with current velocity
 *    and position).
 *
 * 2. Reset themselves to a newly constructed state. This is so the user can
 *    click the reset button after completing a game and have things work as
 *    expected.
 *
 * Please note that here use the upper-left coordinate, which means that the
 * origin point (0.0,0.0) is at the upper left.
 *
 * Also, all arena entities are circular.
 */
class ArenaEntity {
 public:
  ArenaEntity(double radius, const Position& pos,
              const nanogui::Color& color) :
      radius_(radius), pos_(pos), color_(color) {}
  virtual ~ArenaEntity(void) {}

  /**
   * @brief Perform whatever updates are needed for a particular entity after 1
   * timestep (updating position, changing color, etc.).
   */
  virtual void TimestepUpdate(__unused uint dt) {}

  /**
   * @brief Reset the entity to its newly constructed state.
   */
  virtual void Reset(void) {}

  /**
   * @brief Get the name of an entity for visualization purposes, to aid in
   * debugging.
   */
  virtual std::string get_name(void) const = 0;

  void set_pos(const Position& pos) { pos_ = pos; }
  const Position& get_pos(void) const { return pos_; }
  const nanogui::Color& get_color(void) const { return color_; }
  void set_color(const nanogui::Color& color) { color_ = color; }
  double radius(void) const { return radius_; }

 private:
  double radius_;
  Position pos_;
  nanogui::Color color_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_ENTITY_H_ */
