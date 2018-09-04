import math
import turtle

# --------------   CLASS DEFINITIONS -----------------
# ----------------------------------------------------

def Velocity(angle, length):
  x = length*math.cos(angle)
  y = length*math.sin(angle)
  return Vector(x,y)

class Vector:
  def __init__(self, x, y):
    self.x = x
    self.y = y
    self.angle = math.atan2(y,x)
    self.pen = turtle.Turtle()
    self.pen.hideturtle()

  def Draw(self,color="black"):
    self.pen.pu()
    #self.pen.goto(self.ox, self.oy)
    self.pen.goto(0,0)
    self.pen.left(self.angle*180/math.pi)
    self.pen.pd()
    self.pen.color(color)
    #self.pen.goto(int(self.x+self.ox), int(self.y+self.oy))
    self.pen.goto(int(self.x), int(self.y))

  def Clear(self):
    self.pen.clear()

    
class Circle:
  def __init__( self, radius, heading, pos, color ):
    self.radius = radius
    self.pos = pos
    self.heading = heading
    self.color = color
    self.pen = turtle.Turtle()
    self.pen.hideturtle()
    self.vel = Velocity(self.heading, self.radius)
    
  def Draw(self):
    self.pen.pu()
    self.pen.goto(self.pos[0], self.pos[1])
    self.pen.pd()
    self.pen.dot(self.radius*2, self.color)
    
  def DrawHeading(self):
    self.vel.Draw()

  def Clear(self):
    self.pen.clear()
    self.vel.Clear()


# ---------------------------------------------------
def main(wall,test):
  # wall==true, means test walls, else test quadrants
  # test quadrant: 1:NE, 2:NW, 3:SW, 4:SE
  # test wall: 0:right, 1:left, 2:up, 3:down, -1:quadrants instead
  
  if wall:
    # test wall: 0:right, 1:left, 2:up, 3:down, -1:quadrants instead
    if 0 == test:
      collision_angle_rad = math.atan2(0,40)
      heading_angle_rad = math.atan2(10,20)
    elif 1 == test:
      collision_angle_rad = math.atan2(0,-40)
      heading_angle_rad = math.atan2(10,-20)
    elif 2 == test:
      collision_angle_rad = math.atan2(40,0)
      heading_angle_rad = math.atan2(20,10)
    elif 3 == test:
      collision_angle_rad = math.atan2(-40,0)
      heading_angle_rad = math.atan2(-20,10)
    else:
      print('Error'); return
  else:
    # test quadrant: 1:NE, 2:NW, 3:SW, 4:SE
    if 0 == test:
      collision_angle_rad = math.pi/5
      heading_angle_rad = math.pi/7
    elif 1 == test:
      collision_angle_rad = math.pi/2+ math.pi/5
      heading_angle_rad = math.pi/2 + math.pi/7
    elif 2 == test:
      collision_angle_rad = math.pi+math.pi/5
      heading_angle_rad = math.pi+math.pi/7
    elif 3 == test:
      collision_angle_rad = -math.pi/5
      heading_angle_rad = -math.pi/7
    else:
      print('Error'); return

  print('H: ',heading_angle_rad,', ',heading_angle_rad*180/math.pi)
  print('CA: ',collision_angle_rad,', ',collision_angle_rad*180/math.pi)

  radius = 40
  robot = Circle( radius, heading_angle_rad, [ 0,0 ], "yellow")
  stationary = Circle( radius, 0,
                       [2*radius*math.cos(collision_angle_rad), \
                        2*radius*math.sin(collision_angle_rad)], "black")
  print(robot.pos)
  print(stationary.pos)

  robot.Draw()
  robot.DrawHeading()
  stationary.Draw()

  # All code above: this would be set by the actual position and heading
  # of the robot and colliding obstacle. This does assume that the two
  # balls are not overlapping. See flatredball if you want to reposition
  # them to a touching, but not overlapping position

  # This code based on the flatredball resource
  # http://flatredball.com/documentation/tutorials/math/circle-collision/
  # robot = circle 1

  # Determine the point of collision, which also defines the angle
  collision = Vector( stationary.pos[0]-robot.pos[0], \
                      stationary.pos[1]-robot.pos[1] )
  collision.Draw("red")

  # Define the tangent to the point of collision
  collision_tangent = Vector( stationary.pos[1]-robot.pos[1], \
                              -(stationary.pos[0]-robot.pos[0]))
  collision_tangent.Draw("purple")
  print('tangent ',collision_tangent.x,' ', collision_tangent.y)

  # Normalize the tangent by making it of length 1
  tangent_length = (collision_tangent.x**2 + collision_tangent.y**2)**0.5
  normal_tangent = Vector( collision_tangent.x/tangent_length, \
                           collision_tangent.y/tangent_length)
  print('NormTang :',normal_tangent.x,' ',normal_tangent.y)
  normal_tangent.Draw('blue')

  # relative velocity = robot because stationary circle has 0 velocity
  # See flatredball to modify code for 2 moving objects
  rel_velocity = robot.vel
  print('RelVel :',rel_velocity.x,' ',rel_velocity.y)
  rel_velocity.Draw('black')

  # Determine the velocity vector along the tangent
  length = rel_velocity.x*normal_tangent.x + rel_velocity.y*normal_tangent.y
  print('length ',length)
  print('NormTang :',normal_tangent.x,' ',normal_tangent.y)
  tangent_velocity = Vector( normal_tangent.x*length, normal_tangent.y*length)
  print('VonT ',tangent_velocity.x,' ',tangent_velocity.y)
  tangent_velocity.Draw('orange')

  # Determine the velocity vector perpendicular to the tangent
  perpendicular = Vector(rel_velocity.x-tangent_velocity.x, \
                         rel_velocity.y-tangent_velocity.y )
  print("Vperp ",perpendicular.x,' ',perpendicular.y)
  perpendicular.Draw("green")

  # New Heading
  # This is for robot only. See flatredball to move both entities
  new_heading = Vector( (robot.vel.x-2*perpendicular.x), \
                        (robot.vel.y-2*perpendicular.y))
  print('new heading ',new_heading.x,' ',new_heading.y)
  new_heading.Draw("blue")

  input("to continue")
  robot.Clear()
  stationary.Clear()
  collision_tangent.Clear()
  perpendicular.Clear()

def TestWalls():
  for i in range(4):
    main(True,i)

def TestQuadrants():
  for i in range(4):
    main(False,i)

TestWalls()
TestQuadrants()

# ---------------------------------------------------------------
# ---------------------------------------------------------------
# This is identical to above without the printing and drawing ...
def DetermineNewHeading( robot, stationary ):
  
  # Determine the point of collision, which also defines the angle
  collision = Vector( stationary.pos[0]-robot.pos[0], \
                      stationary.pos[1]-robot.pos[1] )

  # Define the tangent to the point of collision
  collision_tangent = Vector( stationary.pos[1]-robot.pos[1], \
                              -(stationary.pos[0]-robot.pos[0]))

  # Normalize the tangent making it length 1
  tangent_length = (collision_tangent.x**2 + collision_tangent.y**2)**0.5
  normal_tangent = Vector( collision_tangent.x/tangent_length, \
                           collision_tangent.y/tangent_length)

  # relative velocity = robot because stationary circle has 0 velocity
  # See flatredball to modify code for 2 moving objects
  rel_velocity = robot.vel

  # Determine the velocity vector along the tangent
  length = rel_velocity.x*normal_tangent.x + rel_velocity.y*normal_tangent.y
  tangent_velocity = Vector( normal_tangent.x*length, normal_tangent.y*length)

  # Determine the velocity vector perpendicular to the tangent
  perpendicular = Vector(rel_velocity.x-tangent_velocity.x, \
                         rel_velocity.y-tangent_velocity.y )

  # New Heading
  # This is for robot only. See flatredball to move both entities
  new_heading = Vector( (robot.vel.x-2*perpendicular.x), \
(robot.vel.y-2*perpendicular.y))
