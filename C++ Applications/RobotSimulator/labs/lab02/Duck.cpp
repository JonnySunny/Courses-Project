//
//  Duck.cpp
//  CSCI3081-Lab1
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#include <iostream>
#include "Duck.h"

using std::cout;
using std::endl;

Duck::Duck() {
}

void Duck::performQuack() {
    cout << "QUACK!!" << endl;
}

std::string Duck::getDescription() {
  std::string descriptionText = "a plain duck";
  return descriptionText;
}
