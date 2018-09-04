//
//  RubberDuck.h
//  CSCI3081-Lab1
//
//  Created by Seth Johnson on 1/24/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef LAB02_RUBBERDUCK_H_
#define LAB02_RUBBERDUCK_H_

#include <string>
#include "Duck.h"

class RubberDuck : public Duck {
public:
    RubberDuck();
    std::string getDescription();
    void performQuack();
};

#endif
