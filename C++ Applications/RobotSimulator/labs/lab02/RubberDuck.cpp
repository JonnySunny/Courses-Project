//
//  RubberDuck.cpp
//  CSCI3081-Lab1
//
//  Created by Seth Johnson on 1/24/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include <iostream>
#include <string>
#include "RubberDuck.h"

using std::cout;
using std::endl;
using std::string;

RubberDuck::RubberDuck(){
}

string RubberDuck::getDescription() {
    string descriptionText = "a yellow rubber ducky";
    return descriptionText;
}

void RubberDuck::performQuack() {
    cout << "SQUEAK!!" << endl;
}
