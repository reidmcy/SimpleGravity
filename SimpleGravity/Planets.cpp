//
//  Planets.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-11.
//  Copyrigh double (c) 2015 Reid. All rights reserved.
//

#include "Planets.h"

void fanHelper(float i[2], float f[2], float r, float theta) {
    f[0] = i[0] + r * cosf(theta);
    f[1] = i[1] + r * sinf(theta);
}


template <class T>
pair<T> operator+(const pair<T> &p1, const pair<T> &p2) {
    return {p1.x + p2.x, p1.y + p2.y};
}

template <class T>
Planet<T>::Planet() {
    qx = qy = vx = vy = 0;
    m = im = h = 1;
    cr = cb = cg = .5;
    lpRun = false;
    //std::cout << "Planet created" << std::endl;
}

template <class T>
Planet<T>::Planet(T qxi, T qyi, T vxi, T vyi, T mi) {
    qx = qxi;
    qy = qyi;
    vx = vxi;
    vy = vyi;
    m = mi;
    im = 1 / m;
    h = 1;
    lpRun = false;
    cr = cb = cg = .5;
}

template <class T>
void Planet<T>::set(T qxi, T qyi, T vxi, T vyi, T mi, T hi) {
    qx = qxi;
    qy = qyi;
    vx = vxi;
    vy = vyi;
    m = mi;
    im = 1 / m;
    h = hi;
    lpRun = false;
}

template <class T>
void Planet<T>::setStep(T hn) {
    h = hn;
}

template <class T>
void Planet<T>::stepEuler(pair<T> g) {
    qx = qx + vx * h;
    qy = qy + vy * h;
    vx = vx + g.x * h * im;
    vy = vy + g.y * h * im;
}

template <class T>
void Planet<T>::stepLeapFrog(pair<T> g) {
    T ax = g.x * im;
    T ay = g.y * im;
    if (!lpRun) {
        vx = vx + ax * h / 2;
        vy = vy + ay * h / 2;
    } else {
    vx = vx + ax * h;
    vy = vy + ay * h;
    }
    qx = qx + vx * h;
    qy = qy + vy * h;
}

template <class T>
void Planet<T>::stepBashforth(pair<T> g) {
    T fx = g.x;
    T fy = g.y;
    if (!lpRun) {
        
    }
    for (int i = 1; i < BashCount; i++) {
        fx += bashVals[i].x;
        fy += bashVals[i].y;
    }
    vx = vx + im * h * fx;
    vy = vy + im * h * fy;
    qx = qx + vx * h;
    qy = qy + vy * h;
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
void Planet<T>::draw(float cx, float cy, T zoom) {
    float loc[2];
    float surface[2];
    loc[0] = (qx - cx) * zoom;
    loc[1] = (qy - cy) * zoom;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(cr, cg, cb);
    glVertex2fv(loc);
    for (int i = 0; i < circlePoints + 1; i ++) {
        fanHelper(loc, surface, pow(10, 11) * zoom, i * M_PI * 2 / circlePoints);
        glVertex2fv(surface);
    }
    glEnd();
}

template <class T>
void Planet<T>::getColour(float c[3]) {
    c[0] = cr;
    c[1] = cg;
    c[2] = cb;
}

template <class T>
void Planet<T>::setColour(float r, float g, float b) {
    cr = r;
    cg = g;
    cb = b;
}

template<class T>
void Planet<T>::setColourToMass() {
    cr = 1;
    cg = cb = m / mMax;
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
    pthreads = new std::thread[count];
}

template <class T>
System<T>::~System<T>() {
    delete [] planets;
    delete [] gField;
    delete [] pthreads;
}


template <class T>
void System<T>::tick(T h) {
    for (int i = 0; i < count; i++) {
        pthreads[i] = std::thread(&System::getField, this, i);
    }
    for (int i = 0; i < count; i++) {
        pthreads[i].join();
        pthreads[i] = std::thread(&Planet<T>::stepLeapFrog, &planets[i], gField[i]);
        //planets[i].stepLeapFrog(gField[i]);
    }
    for (int i = 0; i < count; i++) {
        pthreads[i].join();
    }
}

template <class T>
void System<T>::getField(int c) {
    pair<T> ret = {0, 0};
    for (int i = 0; i < count; i++) {
        if (i != c) {
            ret = ret + planets[i].getField(planets[c].getLocation());
        }
    }
    gField[c] = ret;
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
    for (int i = 0; i < count; i++) {
        planets[i].draw(cx, cy, zoom);
    }
}

template class System<double>;
template class Planet<double>;
template struct pair<double>;