//
//  Setup.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-13.
//  Copyright (c) 2015 Reid. All rights reserved.
//

#include "Setup.h"

static double moveDist = .1;
static double zoomDelta = 1.5;

bool testing = false;
int testingCount = 100;

System<double>* MainSystem;
double cameraX = 0;
double cameraY = 0;
double zoom = 1 / qMax;


template <class T>
System<T> setup(int n, T h, std::string w, int* argc, char* argv[]) {
    glutInit(argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(w.c_str());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> mDist(mMax, mMax);
    std::normal_distribution<T> vDist(-vMax, vMax);
    std::uniform_real_distribution<T> qDist(-qMax, qMax);
    std::normal_distribution<T> cDist(0, 1);
    Planet<T>* P;
    P = new Planet<T>[n];
    for (int i = 0; i < n; i++) {
        T qxi = qDist(gen);
        T qyi = qDist(gen);
        T vxi = (qyi > 0) ? vDist(gen) : (- vDist(gen));
        T vyi = (qxi < 0) ? vDist(gen) : (- vDist(gen));
        P[i].set(qxi, qyi, vxi, vyi, mDist(gen), h);
        P[i].setColour(cDist(gen), cDist(gen), cDist(gen));
    }
    P[0].set(0,0,0,0, mMax * 1000, h);
    P[0].setColour(1,1,1);
    return System<T>(n, P);
}

template <class T>
void mainloop(System<T>* S, int* argc, char* argv[], bool t) {
    testing = t;
    MainSystem = S;
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyb);
    glutSpecialFunc(skeyb);
    glutMainLoop();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    MainSystem->draw(cameraX, cameraY, zoom);
    glutSwapBuffers();
}

void idle() {
    MainSystem->tick(0.1);
    display();
    if (testing) {
        testingCount -= 1;
        if (testingCount <= 0) {
            exit(EXIT_SUCCESS);
        }
    }
}

void keyb(unsigned char k, int x, int y) {
    switch (k) {
        case 27:
            exit(EXIT_SUCCESS);
            break;
        case 'q':
            exit(EXIT_SUCCESS);
            break;
        case '+':
            zoom = zoom * zoomDelta;
            break;
        case '=':
            zoom = zoom * zoomDelta;
            break;
        case '-':
            zoom = zoom / zoomDelta;
        case '_':
            zoom = zoom / zoomDelta;
            break;
        default:
            break;
    }
}

void skeyb(int k, int x, int y) {
    switch (k) {
        case GLUT_KEY_LEFT:
            cameraX -= moveDist / zoom;
            break;
        case GLUT_KEY_RIGHT:
            cameraX += moveDist / zoom;
            break;
        case GLUT_KEY_UP:
            cameraY += moveDist / zoom;
            break;
        case GLUT_KEY_DOWN:
            cameraY -= moveDist / zoom;
            break;
        default:
            break;
    }
}

template System<double> setup<double>(int n, double h, std::string w, int* argc, char* argv[]);
template void mainloop<double>(System<double>* S, int* argc, char* argv[], bool t);