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

template <class T>
System<T> setup(int n, T h, std::string w, int* argc, char* argv[]);

template <class T>
void mainloop(System<T>* S, int* argc, char* argv[]);

void display();
void idle();
void keyb(unsigned char k, int x, int y);
void skeyb(int k, int x, int y);


#endif /* defined(__SimpleGravity__Setup__) */
