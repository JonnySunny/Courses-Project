//
//  Quack.h
//
//  Created by Seth Johnson on 2/4/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef QUACK_H
#define QUACK_H

#include "QuackBehavior.h"

class Quack : public QuackBehavior {
public:
    Quack() {};
    ~Quack() {};
    void quack();
};

#endif
