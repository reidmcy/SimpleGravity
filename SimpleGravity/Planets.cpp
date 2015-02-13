//
//  Planets.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-11.
//  Copyrigh double (c) 2015 Reid. All rights reserved.
//

#include "Planets.h"

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
}

template <class T>
void Planet<T>::set(T qxi, T qyi, T vxi, T vyi, T mi) {
    qx = qxi;
    qy = qyi;
    vx = vxi;
    vy = vyi;
    m = mi;
}

template <class T>
void Planet<T>::step(T gx, T gy, T h) {
    qx = qx + vx * h;
    qy = qy + vy * h;
    vx = vx + gx * h;
    vy = vy + gy * h;
}
/*
template <class T>
pair<T> Planet<T>::getLocation() {
    pair<T> ret = {qx, qy};
    return ret;
}
*/
template <class T>
pair<T> Planet<T>::gfield(T x, T y) {
    T mag = G * m / std::cbrt((x - qx) * (x - qx) + (y - qy) * (y - qy));
    pair<T> ret = {mag * (x - qx), mag * (y - qy)};
    return ret;
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

/*
template <class T>
void System<T>::tick(T h) {
    for (int i = 0; i < count; i++) {
        gField[i] = getField(planets[i].getLocation());
    }
    
}
*/
template <class T>
void System<T>::print() {
    for(int i = 0; i < count; i++) {
        std::cout << "P " << i << "\t";
        planets[i].print();
        std::cout << std::endl;
    }
}


template class System<double>;
template class Planet<double>;
template struct pair<double>;