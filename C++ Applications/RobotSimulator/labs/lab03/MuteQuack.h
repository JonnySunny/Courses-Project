//
//  MuteQuack.h
//
//  Created by Seth Johnson on 2/5/15.
//  Copyright (c) 2015 Seth Johnson. All rights reserved.
//

#ifndef MUTEQUACK_H
#define MUTEQUACK_H

#include "QuackBehavior.h"

class MuteQuack : public QuackBehavior {
public:
    MuteQuack() {};
    ~MuteQuack() {};
    void quack();
};

#endif
