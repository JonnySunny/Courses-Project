//
//  MallardDuck.cpp
//  CSCI3081-Lab1
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#include <iostream>
#include <string>
#include "MallardDuck.h"

using std::cout;
using std::endl;
using std::string;

MallardDuck::MallardDuck() : Duck() {
}

string MallardDuck::getDescription() {
    string descriptionText = "a mallard duck";
    return descriptionText;
}
