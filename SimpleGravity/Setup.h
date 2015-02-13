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
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "Planets.h"

static double mMax = 100000000;
static double vMax = 1;
static double qMax = 100;


template <class T>
System<T> setup(int n, std::string w, int* argc, char* argv[]);

template <class T>
void mainloop(System<T>* S, int* argc, char* argv[]);

void display();
void idle();


#endif /* defined(__SimpleGravity__Setup__) */
