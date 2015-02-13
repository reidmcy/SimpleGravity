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
#include <iostream>
#include <random>

static double G = 6.673 / 100000000000;

template <class T>
struct pair {
    T x;
    T y;
};


template <class T>
class Planet {
    T qx, qy, vx, vy, m;
public:
    Planet();
    Planet(T qxi, T qyi, T vxi, T vyi, T mi);
    ~Planet() = default;
    void set(T qxi, T qyi, T vxi, T vyi, T mi);
    void step(T gx, T gy, T h);
    pair<T> getLocation();
    pair<T> gfield(T x, T y);
    void print();
};

template <class T>
class System {
public:
    int count;
    Planet<T>* planets;
    pair<T>* gField;
    System(int c, Planet<T>* p);
    ~System();
    //void tick(T h);
    //pair<T> getField(pair<T> q);
    void print();
};

#endif /* defined(__SimpleGravity__Planets__) */
