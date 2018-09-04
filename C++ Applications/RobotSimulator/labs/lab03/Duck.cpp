//
//  Duck.cpp
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#include "Duck.h"

#include <iostream>

#include "QuackBehavior.h"
#include "Quack.h"

using std::cout;
using std::endl;

Duck::Duck() {
    m_quackBehavior = NULL;
    setQuackBehavior(new Quack());
    setName("Duck");
}

void Duck::performQuack() {
    m_quackBehavior->quack();
}

void Duck::setQuackBehavior(QuackBehavior* behavior) {
    if (m_quackBehavior != NULL)
        delete m_quackBehavior;
    
    m_quackBehavior = behavior;
}