//
//  Planets.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-11.
//  Copyrigh double (c) 2015 Reid. All rights reserved.
//

#include "Planets.h"

template <class T>
void Planet<T>::step(T gx, T gy, T h) {
    qx = qx + vx * h;
    qy = qy + vy * h;
    vx = vx + gx * h;
    vy = vy + gy * h;
}

template <class T>
pair<T> Planet<T>::gfield(T x, T y) {
    T mag = G * m / std::cbrt((x - qx) * (x - qx) + (y - qy) * (y - qy));
    pair<T> ret = {mag * (x - qx), mag * (y - qy)};
    return ret;
}
template class Planet<double>;
template struct pair<double>;