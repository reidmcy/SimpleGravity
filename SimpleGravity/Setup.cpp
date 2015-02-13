//
//  Setup.cpp
//  SimpleGravity
//
//  Created by Reid on 2015-02-13.
//  Copyright (c) 2015 Reid. All rights reserved.
//

#include "Setup.h"

template <class T>
System<T> setup(int n) {
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


template System<double> setup<double>(int n);