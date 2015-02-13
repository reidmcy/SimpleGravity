//
//  Setup.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-13.
//  Copyright (c) 2015 Reid. All rights reserved.
//

#include "Setup.h"

static double moveDist = .1;

System<double>* MainSystem;
double cameraX, cameraY, zoom;


template <class T>
System<T> setup(int n, std::string w, int* argc, char* argv[]) {
    glutInit(argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(w.c_str());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<T> mDist(mMax / 10, mMax);
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
    cameraX = cameraY = 0;
    zoom = 0.001;
    glutFullScreen();
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
}

void keyb(unsigned char k, int x, int y) {
    switch (k) {
        case 27:
            exit(EXIT_SUCCESS);
            break;
        case '+':
            zoom = zoom * 2;
            break;
        case '=':
            zoom = zoom * 2;
            break;
        case '-':
            zoom = zoom / 2;
        case '_':
            zoom = zoom / 2;
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

template System<double> setup<double>(int n, std::string w, int* argc, char* argv[]);
template void mainloop<double>(System<double>* S, int* argc, char* argv[]);