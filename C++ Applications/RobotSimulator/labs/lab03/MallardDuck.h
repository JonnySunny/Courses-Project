//
//  MallardDuck.h
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include <string>
#include "Duck.h"

class MallardDuck : public Duck {
public:
    MallardDuck();
    ~MallardDuck();
    
    std::string getDescription();
};

#endif 
