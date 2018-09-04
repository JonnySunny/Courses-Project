//
//  MysteryDuck.h
//  CSCI3081-Lab1
//
//  Created by Zhongyi Sun.
//  
//

#ifndef LAB02_MYSTERYDUCK_H_
#define LAB02_MYSTERYDUCK_H_

#include <string>
#include "Duck.h"

using std::cout;
using std::endl;
using std::string;

class MysteryDuck : public Duck {
private:
	string name;
	string sound;
public:
    MysteryDuck(string initname, string initsound);
    std::string getDescription();
    void performQuack();
};

#endif
