
//
//  MysteryDuck.cpp
//  CSCI3081-Lab1
//
//  Created by Zhongyi
//

#include <iostream>
#include <string>
#include "MysteryDuck.h"

using std::cout;
using std::endl;
using std::string;

MysteryDuck::MysteryDuck(string initname, string initsound){
	name = initname;
	sound = initsound; 
}

string MysteryDuck::getDescription() {
    string descriptionText = name;
    return descriptionText;
}

void MysteryDuck::performQuack() {
    cout << sound << endl;
}
