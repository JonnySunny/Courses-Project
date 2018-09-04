
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/sensor_base.h"
#include "../src/sensor_distress.h"
#include "../src/sensor_entity_type.h"
#include "../src/sensor_proximity.h"
#include "../src/sensor_touch.h"

using namespace csci3081;

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST(SensorProximity, Constructor){
  SensorProximity sp;
  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorProximity>::value;
  EXPECT_TRUE(val);
 // EXPECT_EQ(sp.get_activated(), 0);
  EXPECT_EQ(sp.get_fov(), 100);
  EXPECT_EQ(sp.get_range(), 100);
  EXPECT_EQ(sp.get_distance(), 100);
}

TEST(SensorProximixy, Activated_func){
  SensorProximity sp;
  sp.set_activated(1);
  EXPECT_EQ(sp.get_activated(), 1);
}

TEST(SensorProximixy, Accept_func){
  EventProximity* e = new EventProximity();
  e->set_position_of_sensor(Position(1,0));
  e->set_position_of_sensed(Position(1,50));
  e->set_radius_of_sensed(50);
  e->set_heading_angle_of_sensor(20);
  SensorProximity sp;
  sp.Accept(e);
  EXPECT_EQ(sp.get_distance(), 50);
}
TEST(SensorProximity,FildOfView_func){
  SensorProximity sp;
  sp.set_fov(20);
  EXPECT_EQ(sp.get_fov(), 20);
}

TEST(SensorProximity, range_func){
  SensorProximity sp;
  sp.set_range(20);
  EXPECT_EQ(sp.get_range(), 20);
}

TEST(SensorProximity, Distance_func){
  SensorProximity sp;
  sp.set_distance(20);
  EXPECT_EQ(sp.get_distance(), 20);
}

TEST(SensorProximity, In_range_func){
  SensorProximity sp;
  bool ranged = sp.in_range(1,2,3,4);
  EXPECT_EQ(ranged, false);
}

TEST(SensorProximity, Sensor_reading_func){
  SensorProximity sp;
  double distance = sp.sensor_reading(Position(100,150),           Position (200,150), 37, 10);
  EXPECT_EQ(distance, 100);
  double distance_1 = sp.sensor_reading(Position(0,0), Position(125,100), 20, 100);
  EXPECT_EQ(distance_1, -1);
}

TEST(SensorProximity, Reset_func) {
  SensorProximity sp;

  // sp.set_activated(1);
  sp.set_fov(20);
  sp.set_range(20);
  sp.set_distance(20);
  // EXPECT_EQ(sp.get_activated(), 1);
  EXPECT_EQ(sp.get_fov(), 20);
  EXPECT_EQ(sp.get_range(), 20);
  EXPECT_EQ(sp.get_distance(), 20);

  sp.Reset();
  // EXPECT_EQ(sp.get_activated(), 0);
  EXPECT_EQ(sp.get_fov(), 100);
  EXPECT_EQ(sp.get_range(), 100);
  EXPECT_EQ(sp.get_distance(), 100);

}


TEST(SensorDistress, Constructor){
  SensorDistress sd;

  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorDistress>::value;
  EXPECT_TRUE(val);
  EXPECT_EQ(sd.get_activated(), 0);
  // EXPECT_EQ(sd.get_range(), 100);

}

TEST(SensorDistress, Activiated_func){
  SensorDistress sd;
  sd.set_activated(1);
  EXPECT_EQ(sd.get_activated(), 1);
}
TEST(SensorDistress, Accept_func){
  EventDistressCall* e = new EventDistressCall();
  e->set_distressed(true);
  SensorDistress sd;
  sd.Accept(e);
  EXPECT_EQ(sd.get_activated(), 1);
}
TEST(SensorDistress,Range_func){
  SensorDistress sd;
  // sd.set_range(20);
  // EXPECT_EQ(sd.get_range(), 20);
}
TEST(SensorDistress, Sanity) {
  SensorDistress sd;
  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorDistress>::value;
  EXPECT_TRUE(val);
  EXPECT_EQ(sd.get_activated(), 0);
  //EXPECT_EQ(sd.get_range(), 100);
  sd.set_activated(1);
  // sd.set_range(20);
  EXPECT_EQ(sd.get_activated(), 1);
  // EXPECT_EQ(sd.get_range(), 20);
}

TEST(SensorDistress, Reset_func) {
  SensorDistress sd;
  sd.set_activated(1);
  // sd.set_range(20);
  // EXPECT_EQ(sd.get_activated(), 1);
  // EXPECT_EQ(sd.get_range(), 20);
  sd.Reset();
  EXPECT_EQ(sd.get_activated(), 0);
  //EXPECT_EQ(sd.get_range(), 100);
}

TEST(SensorEntityType, Constructor){
  SensorEntityType se;
  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorEntityType>::value;
  EXPECT_TRUE(val);
  // EXPECT_EQ(se.get_activated(), 0);
  // EXPECT_EQ(se.get_range(), 100);
  EXPECT_EQ(se.get_entity_type(), None);
}

TEST(SensorEntityType, Activiated_func){
  //SensorEntityType se;
  //se.set_activated(1);
  //EXPECT_EQ(se.get_activated(), 1);
}

TEST(SensorEntityType, Ranged_func){
  SensorEntityType se;
  //se.set_range(20);
  //EXPECT_EQ(se.get_range(), 20);
}


TEST(SensorEntityType, EntityType_func){
  SensorEntityType se;
  se.set_entity_type(kRobot);
  EXPECT_EQ(se.get_entity_type(), kRobot);
}

TEST(SensorEntityType, Accept_func){
  EventTypeEmit* e = new EventTypeEmit();
  e->set_entity_type(kRobot);
  SensorEntityType se;
  se.Accept(e);
  EXPECT_EQ(se.get_entity_type(), kRobot);
}

TEST(SensorEntityType, Reset_func) {
  SensorEntityType se;
  // se.set_activated(1);
  // se.set_range(20);
  se.set_entity_type(kRobot);

  // EXPECT_EQ(se.get_activated(), 1);
  // EXPECT_EQ(se.get_range(), 20);
  EXPECT_EQ(se.get_entity_type(),kRobot);	

  se.Reset();
  // EXPECT_EQ(se.get_activated(), 0);
  // EXPECT_EQ(se.get_range(), 100);
  EXPECT_EQ(se.get_entity_type(), None);	
}



TEST(SensorTouch, Constructor){
  SensorTouch st;
  bool val = std::is_base_of<csci3081::Sensor, csci3081::SensorTouch>::value;
  EXPECT_TRUE(val);
  EXPECT_EQ(st.get_activated(), 0);
  EXPECT_EQ(st.get_point_of_contact().x, 0);
  EXPECT_EQ(st.get_point_of_contact().y, 0);
  EXPECT_EQ(st.get_angle_of_contact(), 0.0);
}

TEST(SensorTouch, Activated_func){
  SensorTouch st;
  st.set_activated(1);
  EXPECT_EQ(st.get_activated(), 1);
}

TEST(SensorTouch, PointOfContact_func){
  SensorTouch st;
  st.set_point_of_contact(csci3081::Position(1.0, 1.0));
  EXPECT_EQ(st.get_point_of_contact().x, 1.0);
  EXPECT_EQ(st.get_point_of_contact().y, 1.0);
}

TEST(SensorTouch, AngleOfContact_func){
  SensorTouch st;
  st.set_angle_of_contact(1);
  EXPECT_EQ(st.get_angle_of_contact(), 1);
}

TEST(SensorTouch, Accept_func){
  EventCollision* e = new EventCollision();
  e->set_collided(true);
  e->set_point_of_contact(Position(10,100));
  e->set_angle_of_contact(20);
  SensorTouch st;
  st.Accept(e);
  EXPECT_EQ(st.get_point_of_contact().x, 10);
    EXPECT_EQ(st.get_point_of_contact().y, 100);
  EXPECT_EQ(st.get_angle_of_contact(), 20);
}

TEST(SensorTouch, Reset_func) {
  SensorTouch st;
  st.set_activated(1);
  st.set_point_of_contact(csci3081::Position(1.0, 1.0));
  st.set_angle_of_contact(45.0);
  EXPECT_EQ(st.get_activated(), 1);
  EXPECT_EQ(st.get_point_of_contact().x, 1.0);
  EXPECT_EQ(st.get_point_of_contact().y, 1.0);
  EXPECT_DOUBLE_EQ(st.get_angle_of_contact(), 45.0);

  st.Reset();
  EXPECT_EQ(st.get_angle_of_contact(), 0.0);
    EXPECT_EQ(st.get_point_of_contact().x, 0.0);
  EXPECT_EQ(st.get_point_of_contact().y, 0.0);
  EXPECT_EQ(st.get_activated(), 0);
}


