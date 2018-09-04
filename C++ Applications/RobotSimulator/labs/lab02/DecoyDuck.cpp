//
//  DecoyDuck.cpp
//  CSCI3081-Lab1
//
//  Created by Zhongyi
//

#include <iostream>
#include <string>
#include "DecoyDuck.h"

using std::cout;
using std::endl;
using std::string;

DecoyDuck::DecoyDuck(){
}

string DecoyDuck::getDescription() {
    string descriptionText = "a plastic decoy duck";
    return descriptionText;
}

void DecoyDuck::performQuack() {
    cout << "..." << endl;
}
