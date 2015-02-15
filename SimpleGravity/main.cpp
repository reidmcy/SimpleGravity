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

std::string window = "SimpleGravity";
int planetCount = 2000; //tests at 200
double step = 100; //tests at 100

bool test = true;

int main(int argc, char * argv[]) {
    System<double> S = setup<double>(planetCount, step, window, &argc, argv);
    mainloop<double>(&S, &argc, argv, test);
}

/*
basic : 2.6
multithreading : 2.6
*/