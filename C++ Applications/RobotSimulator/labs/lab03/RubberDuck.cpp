//
//  RubberDuck.cpp
//
//  Created by Seth Johnson on 1/24/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#include <iostream>
#include <string>
#include "RubberDuck.h"
#include "Squeak.h"

using std::cout;
using std::endl;
using std::string;

RubberDuck::RubberDuck() {
    setQuackBehavior(new Squeak());
}

RubberDuck::~RubberDuck() {}

string RubberDuck::getDescription() {
    string descriptionText = "a yellow rubber ducky";
    return descriptionText;
}


