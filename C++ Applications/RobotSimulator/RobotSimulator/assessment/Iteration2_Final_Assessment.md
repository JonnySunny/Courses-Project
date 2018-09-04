# Iteration 2 Feedback

*Grader: Sam - marqu317@umn.edu*

This file contains the feedback for your iteration 2. If you have questions or concerns, please reach out to me (Sam) and we can resolve them.

Note: This file entails 2 separate components of the iteration 2 grading: Code Submission and refactoring/unit tests. Code submission is the grade on your final code turn in for interfaces, function, etc. Refactoring/Unit tests refers to the initialization refactor you did and the unit tests your wrote for the sensors.

## Refactoring and Unit Tests

This is the grade for the initialization refactor you were asked to do and the sensor unit tests you turned in early in interation 2.



| **Category**                                  | **Score** | **Comments** |
|-----------------------------------------------|-----------|--------------|
| Refactor Initialization | 15 / 15 |  |
| Unit Tests for Sensors (needs 5) | 15 / 15 |  |
| **Total** | 30 / 30 |   |

## Code

This section details the functional components of your iteration 2. See the requirement write-up for iteration 2 for more detail about each listed category.



| **Category**                                  | **Score** | **Comments** |
|-----------------------------------------------|-----------|--------------|
| P1 - Define `enum entity_type` | 4 / 4 |  |
| P1 - Interface for abstract class Sensor | 4 / 4 |  |
| P1 - Interface & members for SensorProximity class | 4 / 4 |  |
| P1 - Interface & members for SensorDistress class | 4 / 4 |  |
| P1 - Interface & members for SensorEntityType class | 4 / 4 |  |
| P1 - Revise interface & members for SensorTouch | 4 / 4 |  |
| P1 - Interface & members for Events | 4 / 4 |  |
| P1 - Define abstract MotionHandler class | 4 / 4 |  |
| P1 - Define various motion handler classes | 4 / 4 |  |
| P1 - Rename Robot class to Player | 4 / 4 |  |
| P1 - Interface & members for a Robot class | 5 / 5 |  |
| P1 - Interface & members for a SuperBot class | 5 / 5 | Could this be a subclass of Robot? or even the same class!? |
| P2 - Interface for Arena Methods modeled after Observer pattern | 7 / 10 | You have register and unregister functions. Yay. I don't see the registered sensors being used, but I do see some events being passed to entities. |
| P2 - Implement functionality in Arena for checking events | 5 / 10 | I'm confused as to why other events are wrapped in the collide requirement. Distress doesn't seem to be implemented as designed. proximity doesn't get passed anywhere or really calculated. |
| P3 - Implement Accept methods for each sensor | 2 / 2 |  |
| P3 - Implement functionality for Player, including sensors and events | 6 / 8 | No freezing seen. |
| P3 - Implement functionality for Robot | 4 / 8 | freezing, proximity sensors, etc unimplemented. |
| P3 - Implement functionality for SuperBot | 2 / 8 | Seems like a copy and paste of the other classes. |
| P3 - Implement functionality for HomeBase and RechargeStation | 1 / 2 | Homebase new functionality not ther. |
| P3 - Implement win / loss conditions | 0 / 2 | No new win/loss condiitions |
| Additional Marks | 0 / 0 | Good interfaces. More implementation needs to be done and flush out how you're using the Observer pattern. |
| **Total** | 77 / 100 |   |

