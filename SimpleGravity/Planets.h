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
#include <thread>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


static double mMax = pow(10, 25);
static double vMax = pow(10, 8);
static double qMax = pow(10, 12);

static int circlePoints = 16;
static double G = 6.673 / 100000000000; //N * m^2 / kg^2

template <class T>
struct pair {
    T x;
    T y;
};


template <class T>
class Planet {
    float cr, cb, cg;
    T qx, qy, vx, vy, m, h;
    bool lpRun;
public:
    Planet();
    Planet(T qxi, T qyi, T vxi, T vyi, T mi);
    ~Planet() = default;
    void set(T qxi, T qyi, T vxi, T vyi, T mi, T hi);
    void setStep(T hn);
    void stepEuler(pair<T> l);
    void stepLeapFrog(pair<T> l);
    pair<T> getLocation();
    void getLocation(float l[2]);
    pair<T> getField(pair<T> l);
    void draw(float cx, float cy, T zoom);
    void getColour(float c[3]);
    void setColour(float r, float g, float b);
    void setColourToMass();
    void print();
};

template <class T>
class System {
public:
    int count;
    std::thread* pthreads;
    Planet<T>* planets;
    pair<T>* gField;
    System(int c, Planet<T>* p);
    ~System();
    void tick(T h);
    void getField(int c);
    void print();
    void draw(T cx, T cy, T zoom);
};

#endif /* defined(__SimpleGravity__Planets__) */
