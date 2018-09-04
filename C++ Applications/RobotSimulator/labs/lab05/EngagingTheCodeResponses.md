## Exercise to Engage the Code

These are questions that ask you to explore the code in a specific way. They highlight important functionality and flow-of-control. You might want to jot down the answers for your own use as you spend time learning the code. It will probably take you a minimum of 2 hours just to understand how all the pieces fit together. We highly recommend you spend time understanding the framework before adding a single line of code.

# Answer the Following Questions Based on Iteration1 Code

1. What does GraphicsArenaViewer::DrawUsingNanoVG() do?
   Initialize the arena and draw robots, obstacles. also use buttons and keys on the keuboard to control robots and change the color or some things eles on the obejcts.
	
2. When does this get called?
   in the main, which means when the user start, it will be called 

3. How is it that the Recharge Station is being drawn - there is no command to draw it?
   Being draw by this GraphicsArenaViewer::DrawObstacle, and the nvgText will receive "Recharge Station" as its name.

4. What entities exist in the Arena?
    - For each entity, what is it's base (parent) class?
 			base class
   Robot             arena mobile entity
   Recharge Station  obstacle
   Obstacle          arena immobile entity
   HomeBase          arena immobile entity

5. Where does the system check for collisions (look in Arena.cc)?
   home base has collision with robot
   recharge station has collision with robot
   Entity has collision with another entity

6. When does this happen (i.e. where is it in flow-of-control)?
   Check two position first, and 
   when the position with in a delta, which is computed and returned by collision_delta(), collison happens and change the angle for robots

7. What is the logic for checking for colliding with walls?
   check right wall, left, bottom wall, top wall. Then change the angle for robots according to different situations. 

8. What is the logic for checking for colliding with other entities?
   check the distance between two entities via mathematics

9. Trace the EventCollision from the point at which it is created in Arena to
the robot sensor. What does the sensor record when a collision happens?
   record true is collision happend, the change the point and angle according to EventCollision

10. The RobotMotionHandler reads the touch sensor. What does it do with this information?
    if the collision happened, then the headind angle will be changed

11. Identify the method (function) that updates the robot position. Trace flow-of-control
from the call UpdateSimulation in GraphicsArenaViewer.

    RobotMotionBehavior::UpdatePosition()
    if it is not paused, then record time to arena_AdbanceTime, print Advanicng simmulation time by how many timesteps. and for every obstables, updateEntitiesTimestep.

12. What is the equation used to calculate the deltaX and deltaY for the robot
and update the position?

     distance for those two robots is std::sqrt(std::pow(ent2_x - ent1_x, 2) + std::pow(ent2_y - ent1_y, 2));
    So deltax is ent2_x - ent1_x, and delta y is ent2_y - ent1_y
    find the updatePosition in the Robot MotionBehavior 
       // Movement is always along the heading_angle (i.e. the hypotenuse)
 	 new_pos.x += cos(ent->heading_angle()*M_PI/180.0)*ent->speed()*dt;
 	 new_pos.y += sin(ent->heading_angle()*M_PI/180.0)*ent->speed()*dt;
