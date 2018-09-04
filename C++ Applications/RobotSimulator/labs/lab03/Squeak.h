//
//  Squeak.h
//
//  Created by Seth Johnson on 2/5/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef SQUEAK_H
#define SQUEAK_H

#include "QuackBehavior.h"

class Squeak : public QuackBehavior {
public:
    Squeak() {};
    ~Squeak() {}
    void quack();    
};

#endif
