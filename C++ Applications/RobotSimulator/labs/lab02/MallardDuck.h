//
//  MallardDuck.h
//  CSCI3081-Lab1
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#ifndef LAB02_MALLARDDUCK_H_
#define LAB02_MALLARDDUCK_H_

#include <string>
#include "Duck.h"

class MallardDuck : public Duck {
public:
    MallardDuck();
    std::string getDescription();
};

#endif
