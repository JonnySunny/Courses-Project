/**
 * @file event_keypress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_KEYPRESS_H_
#define SRC_EVENT_KEYPRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/event_commands.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An event representing that a key on the keyboard has been
 * pressed.
 *
 * They are sent from the graphics framework to the \ref GraphicsArenaViewer,
 * where they are interpreted further
 */
class EventKeypress : public EventBaseClass {
 public:
  explicit EventKeypress(int key) : key_(key) {}

  void EmitMessage(void) override { printf("Keypress command received\n"); }

 private:
  enum event_commands keypress_to_cmd(int key);
  int key_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_KEYPRESS_EVENT_H_ */
