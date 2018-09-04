//
//  Duck.h
//  CSCI3081-Lab1
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#ifndef LAB02_DUCK_H_
#define LAB02_DUCK_H_

#include <string>

class Duck {
public:
    Duck();
    virtual void performQuack();
    virtual std::string getDescription();
};

#endif
