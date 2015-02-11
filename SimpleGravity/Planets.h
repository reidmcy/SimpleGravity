//
//  Planets.h
//  SimpleGravity
//
//  Created by Reid on 2015-02-11.
//  Copyright (c) 2015 Reid. All rights reserved.
//

#ifndef __SimpleGravity__Planets__
#define __SimpleGravity__Planets__

#include <cmath>

double G = 6.673 / 100000000000;


//template <class T>
struct pair {
    T x;
    T y;
};


template <class T>
class Planet {
public:
    T qx, qy, vx, vy, m;
    void step(T gx, T gy, T h);
    pair<T> gfield(T x, T y);
};

#endif /* defined(__SimpleGravity__Planets__) */
