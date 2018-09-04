//
//  main.cpp
//  CSCI3081-Lab1
//
//  Created by Sarit Ghildayal on 1/24/15.
//  Copyright (c) 2015 Sarit Ghildayal. All rights reserved.
//

#include <iostream>
#include "MallardDuck.h"
#include "RubberDuck.h"
#include "DecoyDuck.h"
#include "MysteryDuck.h"

using std::cout;
using std::endl;
using std::string;
int main() {

    // Create Ducks
    Duck jane;
    MallardDuck maloy;
    RubberDuck lemon;
    DecoyDuck dav;
    MysteryDuck bav("a mystery duck", "!!");
    cout << endl;

    // Introduce a generic duck
    cout << "This" << " is " << jane.getDescription() << " who says ";
    jane.performQuack();
    cout << endl;

    // Introduce a mallard duck
    cout << "This" << " is " << maloy.getDescription() << " who says " ;
    maloy.performQuack();
    cout << endl;

    // Introduce a rubber duck
    cout << "This" << " is " << lemon.getDescription() << " who says " ;
    lemon.performQuack();
    cout << endl;

    // Introduce a decoy duck
    cout << "This" << " is " << dav.getDescription() << " who says " ;
    dav.performQuack();
    cout << endl;

   // Introduce a Mystery duck
    cout << "This" << " is " << bav.getDescription() << " who says " ;
    bav.performQuack();
    cout << endl;

    // I had to type the same thing over and over.
    // I think I can do better by wrapping it in a loop!
    // BUT WAIT, look at the output - it doesn't work! More on this later ...
    Duck ducks[5];
    ducks[0] = jane;
    ducks[1] = maloy;
    ducks[2] = lemon;
    ducks[3] = dav;
    ducks[4] = bav;
    for (int i = 0; i <5 ; i++) {
      cout << "This is " << ducks[i].getDescription() << " who says ";
      ducks[i].performQuack();
    }
    cout << endl;

    return 0;
}
