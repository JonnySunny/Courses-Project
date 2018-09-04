#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

#define DB_DEFAULT 10

using namespace std;

//-----------------------------------------------
//   QUACKING

// Type Polymorphic because of the the QuackBehavior class being abstract
// due to the virtual void quack() = 0
class QuackBehavior {
protected:
  double volume;
public:
  QuackBehavior() : volume(DB_DEFAULT) {}
  virtual string quack() = 0;
};

class Quack : public QuackBehavior {
public:
  Quack() {}
   string quack() {
    stringstream stream;
    string duck_volume;
    string result_str;
    stream << volume;
    stream >> duck_volume;
    string str1="Quack at";
    string str2="decibels.";
    result_str= str1+" "+duck_volume+" "+str2;
    return result_str;
  }
};

class Mute : public QuackBehavior {
public:
  Mute() { volume = 0; }
  string quack() {
    string duck_quack= "Cannot talk.";
    return  duck_quack;
  }
};

class Squeak : public QuackBehavior {
public:
  Squeak() {}
  Squeak(int d) { volume = d; }
  string quack() {
    stringstream stream;
    string duck_volume;
    string result_str;
    stream << volume;
    stream >> duck_volume;
    string str1="Quack at";
    string str2="decibels.";
    result_str= str1+" "+duck_volume+" "+str2;
    return result_str;
  }
};

class Honk : public QuackBehavior {
public:
  Honk() {}
  string quack() {
    stringstream stream;
    string duck_volume;
    string result_str;
    stream << volume;
    stream >> duck_volume;
    string str1="Quack at";
    string str2="decibels.";
    result_str= str1+" "+duck_volume+" "+str2;
    return result_str;
   }
};
