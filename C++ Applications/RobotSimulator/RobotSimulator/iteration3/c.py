import turtle
import math

# The documentation is minimal. The best way to understand it is to run it and look at the graphics.
# The functions InRange and SensorReading is the logic you will want to copy into iteration2 code.

def Positive(angle):
  # make every angle positive in range 0 to 360
  if angle<0:
    return 360+angle
  if angle>360:
    return angle % 360
  return angle

class Position:
  def __init__(self, x, y):
    self.x = x
    self.y = y
    
class SensorCone:
  # Proximity sensor rendering. Distance is from center of robot.
  # fov: field of view, centered on heading of robot
  def __init__(self, entity, distance, fov ):
    # param entity: robot entity to which it belongs
    self.entity = entity
    self.distance = distance
    self.fov = fov
    self.pen = turtle.Turtle()
    self.pen.hideturtle()
    self.pen.speed(0)

  def Draw(self):
    # Draw perimeter around entire robot, but then show limited fov
    self.pen.pu()
    self.pen.goto(self.entity.pos.x, self.entity.pos.y)
    self.pen.setheading(self.entity.heading_deg)
    self.pen.pd()
    self.pen.dot(self.distance*2,'yellow')
    # draw the cone
    self.pen.left(self.fov//2)
    for i in [0,1,1]:
      self.pen.right((self.fov//2)*i)
      self.pen.pd()
      self.pen.forward(self.distance)
      self.pen.pu()
      self.pen.goto(self.entity.pos.x, self.entity.pos.y)
  
class Robot:
  def __init__( self, radius, heading, pos, color ):
    self.radius = radius
    self.pos = pos
    self.heading_deg = Positive(heading)
    self.color = color
    self.pen = turtle.Turtle()
    self.pen.hideturtle()
    self.pen.speed(0)
    # default value of 3*radius for proximity sensor
    self.sensor = SensorCone( self, radius*3, 100)

  def Draw(self):
    self.pen.pu()
    self.pen.goto(self.pos.x, self.pos.y)
    self.pen.pd()
    self.pen.dot(self.radius*2,self.color)
    self.pen.pu()

  def DrawSensor(self):
    self.sensor.Draw()

  def DrawTriangle(self, width_angle, dir_angle, dist):
    # this is the triangle formed by this robot and the one being sensed
    self.pen.pu()
    self.pen.goto(self.pos.x, self.pos.y)
    self.pen.setheading(dir_angle)
    self.pen.right(width_angle)
    self.pen.pd()
    self.pen.forward(dist)
    self.pen.pu()
    self.pen.goto(self.pos.x, self.pos.y)
    self.pen.setheading(dir_angle)
    self.pen.left(width_angle)
    self.pen.pd()
    self.pen.forward(dist)

def InRange( range1, range2 ):
  if range1[0] > range1[1]:
    range1 = [ range1[1], range1[0]]
  if range2[0] > range2[1]:
    range2 = [ range2[1], range2[0]]
  if range2[0] >= range1[0] and range2[0] <= range1[1]:
    return True
  if range2[1] >= range1[0] and range2[1] <= range1[1]:
    return True
  return False

def SensorReading( r_sensing, r_sensed):
  deltaX = r_sensed.pos.x-r_sensing.pos.x
  deltaY = r_sensed.pos.y-r_sensing.pos.y
  dist = (deltaX**2 + deltaY**2)**0.5
  if dist > r_sensing.sensor.distance + r_sensed.radius:
    return False
  # triangle is formed from center of r_sensing to the point along the tangents
  # to r_sensed. The height is dist and the width is r_sensed.radius*2.
  triangle_theta = Positive(math.atan(r_sensed.radius/dist)*180/3.14)
  distance_theta = Positive(math.atan2(deltaY, deltaX)*180/3.14)
  r_sensing.DrawTriangle(triangle_theta, distance_theta, dist)
  sensor_lower = r_sensing.heading_deg - r_sensing.sensor.fov//2
  sensor_upper = r_sensing.heading_deg + r_sensing.sensor.fov//2
  sensed_lower = distance_theta - triangle_theta
  sensed_upper = distance_theta + triangle_theta
  if InRange( [ sensor_lower, sensor_upper ], \
              [ sensed_lower, sensed_upper ] ):
    print('True: ', dist)
  else:
    print('False')


R = Robot( 50, 83, Position(0,0), 'green')
R2 = Robot( 40, 90, Position(100,100),'red')
R.DrawSensor()
R.Draw()
R2.Draw()
SensorReading( R, R2)
