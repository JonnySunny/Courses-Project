#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

//#define DB_DEFAULT 10
using namespace std;


//----------------------------------------------
//  THE DUCKS
#include "FlyBehavior.h"
#include "QuackBehavior.h"

class Duck {
protected:
  FlyBehavior *flyBehavior;
  QuackBehavior *quackBehavior;
public:
  Duck() { }
  virtual string display() = 0;
  string performFly() { return flyBehavior->fly(); }
  string performQuack() { return quackBehavior->quack(); }
  void setFlyBehavior(FlyBehavior *fb) {delete flyBehavior; flyBehavior = fb;}
  void setQuackBehavior(QuackBehavior *qb) {delete quackBehavior; quackBehavior = qb;}
};

class Mallard : public Duck {
public:
  Mallard() {
    flyBehavior = new FlyWithWings();
    quackBehavior = new Quack();
  }
  std::string display() {
    std::string result_str="I am a Mallard.";
    return result_str;
  }

};

class RubberDuck : public Duck {
public:
  RubberDuck() {
    flyBehavior =  new NoFly();
    quackBehavior = new Squeak(2);
  }
  std::string display() {
    std::string result_str="I am a Rubber Duck.";
    return result_str;
  }
};
