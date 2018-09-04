#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

#define MPH_DEFAULT 5

using namespace std;

//-----------------------------------------------
//   FLYING

//  The FlyBehavior class is not polymorphic because we did not make this
//  class abstract.  Note that fly() is not a pure virtual function in this
//  class (see the quack() up above that makes QuackBehavior abstract)
class FlyBehavior {
protected:
  double milesPerHour;
public:
  FlyBehavior() : milesPerHour(MPH_DEFAULT) {}
  virtual string fly() {
    stringstream stream;
    string fly_speed;
    string result_str;
    stream << milesPerHour;
    stream >> fly_speed;
    string str1="Generic Flying at";
    string str2="mph.";
    result_str= str1+" "+fly_speed+" "+str2;
    return result_str;
 }
};

class FlyWithWings : public FlyBehavior {
public:
  FlyWithWings() {}
    string fly() {
    stringstream stream;
    string fly_speed;
    string result_str;
    stream << milesPerHour;
    stream >> fly_speed;
    string str1="Fly with wings at speed of";
    string str2="mph.";
    result_str= str1+" "+fly_speed+" "+str2;
    return result_str;
  }
};

class NoFly : public FlyBehavior {
public:
  NoFly() {}
  string fly() {
    string result_str="Cannot fly.";
    return result_str;
   }
};

class FlyWithRocket : public FlyBehavior {
public:
  FlyWithRocket(){milesPerHour=20;}
  string fly() {
    stringstream stream;
    string fly_speed;
    string result_str;
    stream << milesPerHour;
    stream >> fly_speed;
    string str1="Fly with wings at speed of";
    string str2="mph.";
    result_str= str1+" "+fly_speed+" "+str2;
    return result_str;
  }
};
