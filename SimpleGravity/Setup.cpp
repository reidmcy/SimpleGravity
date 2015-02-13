//
//  Setup.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-13.
//  Copyright (c) 2015 Reid. All rights reserved.
//

#include "Setup.h"

System<double>* MainSystem;

template <class T>
System<T> setup(int n, std::string w, int* argc, char* argv[]) {
    glutInit(argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(w.c_str());
    std::mt19937 gen(902210);
    std::normal_distribution<T> mDist(0, mMax);
    std::normal_distribution<T> vDist(-vMax, vMax);
    std::normal_distribution<T> qDist(-qMax, qMax);
    Planet<T>* P;
    P = new Planet<T>[n];
    for (int i = 0; i < n; i++) {
        P[i].set(qDist(gen), qDist(gen), vDist(gen), vDist(gen), mDist(gen));
    }
    return System<T>(n, P);
}

template <class T>
void mainloop(System<T>* S, int* argc, char* argv[]) {
    MainSystem = S;
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    glutSwapBuffers();
}

void idle() {
    display();
}

template System<double> setup<double>(int n, std::string w, int* argc, char* argv[]);
template void mainloop<double>(System<double>* S, int* argc, char* argv[]);