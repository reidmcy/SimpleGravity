//
//  Setup.h
//  SimpleGravity
//
//  Created by Reid on 2015-02-13.
//  Copyright (c) 2015 Reid. All rights reserved.
//

#ifndef __SimpleGravity__Setup__
#define __SimpleGravity__Setup__

#include <random>

#include "Planets.h"

static double mMax = 10;
static double vMax = 10;
static double qMax = 100;


template <class T>
System<T> setup(int n);


#endif /* defined(__SimpleGravity__Setup__) */
