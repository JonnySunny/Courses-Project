//
//  Duck.h
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#ifndef DUCK_H
#define DUCK_H

#include <string>

class QuackBehavior;


class Duck {
public:
    Duck();
    virtual ~Duck() {};
    
    virtual void performQuack();

    virtual std::string getDescription() = 0;

    std::string getName() {return m_name;}
    void setName(std::string name ) {m_name = name;}
    void setQuackBehavior(QuackBehavior * behavior);
protected:
    std::string m_name;

    QuackBehavior * m_quackBehavior;
    
};

#endif
