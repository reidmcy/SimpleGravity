//
//  Planets.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-11.
//  Copyrigh double (c) 2015 Reid. All rights reserved.
//

#include "Planets.h"

template <class T>
pair<T> operator+(const pair<T> &p1, const pair<T> &p2) {
    return {p1.x + p2.x, p1.y + p2.y};
}

template <class T>
Planet<T>::Planet() {
    qx = qy = vx = vy = m = 0;
    //std::cout << "Planet created" << std::endl;
}

template <class T>
Planet<T>::Planet(T qxi, T qyi, T vxi, T vyi, T mi) {
    qx = qxi;
    qy = qyi;
    vx = vxi;
    vy = vyi;
    m = mi;
    h = 1;
    lpRun = false;
}

template <class T>
void Planet<T>::set(T qxi, T qyi, T vxi, T vyi, T mi, T hi) {
    qx = qxi;
    qy = qyi;
    vx = vxi;
    vy = vyi;
    m = mi;
    h = hi;
    lpRun = false;
}

template <class T>
void Planet<T>::setStep(T hn) {
    h = hn;
}

template <class T>
void Planet<T>::stepEuler(pair<T> l) {
    qx = qx + vx * h;
    qy = qy + vy * h;
    vx = vx + l.x * h / m;
    vy = vy + l.y * h / m;
}

template <class T>
void Planet<T>::stepLeapFrog(pair<T> l) {
    T ax = m * l.x;
    T ay = m * l.y;
    if (lpRun == false) {
        lpvx = vx + ax * h / 2;
        lpvy = vy + ay * h / 2;
    } else {
    lpvx = lpvx + ax * h;
    lpvy = lpvy + ay * h;
    }
    qx = qx + lpvx * h;
    qy = qy + lpvy * h;
}

template <class T>
pair<T> Planet<T>::getLocation() {
    pair<T> ret = {qx, qy};
    return ret;
}
template <class T>
void Planet<T>::getLocation(float l[2]) {
    l[0] = (float) qx;
    l[1] = (float) qy;
}

template <class T>
pair<T> Planet<T>::getField(pair<T> l) {
    T mag =  - G * m / std::cbrt((l.x - qx) * (l.x - qx) + (l.y - qy) * (l.y - qy));
    pair<T> ret = {mag * (l.x - qx), mag * (l.y - qy)};
    return ret;
}

template <class T>
void Planet<T>::getColour(float c[3]) {
    c[0] = 1;
    c[1] = c[2] = m / mMax;
}

template <class T>
void Planet<T>::print() {
    std::cout << "qx " << qx << "\t" << "qy " << qy << "\t";
    std::cout << "vx " << vx << "\t" << "vy " << vy << "\t";
    std::cout << "m " << m << std::endl;
}

template <class T>
System<T>::System(int c, Planet<T>* p) {
    planets = p;
    count = c;
    gField = new pair<T>[c];
}

template <class T>
System<T>::~System<T>() {
    delete [] planets;
}


template <class T>
void System<T>::tick(T h) {
    for (int i = 0; i < count; i++) {
        gField[i] = getField(i);
    }
    for (int i = 0; i < count; i++) {
        planets[i].stepEuler(gField[i]);
    }
}

template <class T>
pair<T> System<T>::getField(int c) {
    pair<T> ret = {0, 0};
    for (int i = 0; i < count; i++) {
        if (i != c) {
            ret = ret + planets[i].getField(planets[c].getLocation());
        }
    }
    return ret;
}

template <class T>
void System<T>::print() {
    for(int i = 0; i < count; i++) {
        std::cout << "P " << i << "\t";
        planets[i].print();
        std::cout << std::endl;
    }
}

template <class T>
void System<T>::draw(T cx, T cy, T zoom) {
    glBegin(GL_POINTS);
    float loc[2];
    float colour[3];
    for (int i = 0; i < count; i++) {
        planets[i].getLocation(loc);
        loc[0] = (loc[0] - cx) * zoom;
        loc[1] = (loc[1] - cy) * zoom;
        planets[i].getColour(colour);
        glColor3fv(colour);
        glVertex2fv(loc);
    }
    glEnd();
}

template class System<double>;
template class Planet<double>;
template struct pair<double>;