//
//  main.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-11.
//  Copyright (c) 2015 Reid. All rights reserved.
//

#include <iostream>
#include <random>
#include "Planets.h"
#include "Setup.h"

int main(int argc, const char * argv[]) {
    System<double> S = setup<double>(2);
    S.print();
    S.tick(10);
    S.print();
}
