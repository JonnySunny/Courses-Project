//
//  QuackBehavior.h
//
//  Created by Seth Johnson on 2/4/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef QUACKBEHAVIOR_H
#define QUACKBEHAVIOR_H

#include <stdio.h>

class QuackBehavior {
public:
    QuackBehavior() {};
    virtual ~QuackBehavior() {}
    virtual void quack() = 0;
};
#endif /* defined(__Minimal_Duck__QuackBehavior__) */
