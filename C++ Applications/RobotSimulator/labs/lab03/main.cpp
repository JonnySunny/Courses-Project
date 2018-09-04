//
//  main.cpp
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#include <iostream>
#include "MallardDuck.h"
#include "RubberDuck.h"
#include "DecoyDuck.h"
#include "MuteQuack.h"

#include <vector>

using std::cout;
using std::endl;
using std::vector;

void introduceDuck(Duck* duck);
void shushDuck(Duck* duck);

int main(int argc, const char * argv[]) {

    // Create Ducks
    Duck * steve = new MallardDuck();
    Duck * charles = new RubberDuck();
    Duck * edmund = new DecoyDuck();
    
    steve->setName("Steve");
    charles->setName("Charles");
    edmund->setName("Edmund");
    
    Duck ** duckArray = new Duck* [10]; // Make room for 10 ducks
    int duckCount = 0; // This will increase by one everytime we add a
    duckArray[duckCount++] = steve;
    duckArray[duckCount++] = charles;
    //duckArray[duckCount++] = edmund;


    // Introduce all the ducks
    cout << "\nHere we have " << duckCount << " ducks." << endl;
    for (int i = 0; i < duckCount; i++) {
        Duck* current_duck = duckArray[i];
        introduceDuck(current_duck);
    }

    // Tell steve to be quiet
    cout << endl;
    shushDuck(steve);

    // Re-introduce all the ducks
    cout << "\nHere we have " << duckCount << " ducks." << endl;
    for (int i = 0; i < duckCount; i++) {
        Duck* current_duck = duckArray[i];
        introduceDuck(current_duck); 
    }

    return 0;
}

void introduceDuck(Duck* duck) {
    cout << duck->getName() << " is " << duck->getDescription() << " who says: ";
    duck->performQuack();
}

void shushDuck(Duck* duck) {
    cout << "\"Shhhh, " << duck->getName() << "!\"" << endl;
    duck->setQuackBehavior(new MuteQuack());
}