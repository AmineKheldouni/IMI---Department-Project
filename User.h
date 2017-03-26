//
// Created by amine on 25/03/17.
//

#ifndef PROJET_USER_H
#define PROJET_USER_H

#include "Plane.h"

class User {
    const int nbPlanes = 2;
    const int nbParts = 3;
    vector<Plane> A;

public:
    User();
    User(const vector<Plane> &A);
    vector<Plane> getPlanes();
    double findCost();
    void addPlane(const Plane p);
};

#endif //PROJET_USER_H
