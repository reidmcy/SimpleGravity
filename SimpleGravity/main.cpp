//
//  main.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-11.
//  Copyright (c) 2015 Reid. All rights reserved.
//

#include <iostream>
#include "Planets.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Planet<double> P;
    P.step(10, 10, 10);
    P.gfield(2, 2);
    std::cout << "Hello, World!\n";
    return 0;
}
