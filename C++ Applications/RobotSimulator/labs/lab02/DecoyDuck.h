//
//  DecoyDuck.h
//  CSCI3081-Lab1
//
//  Created by Zhongyi Sun.
//  
//

#ifndef LAB02_DECOYDUCK_H_
#define LAB02_DECOYDUCK_H_

#include <string>
#include "Duck.h"

class DecoyDuck : public Duck {
public:
    DecoyDuck();
    std::string getDescription();
    void performQuack();
};

#endif
