//
// Created by amine on 25/03/17.
//

#include "User.h"



User::User() {
    vector<PlanePart> planeParts;
    //vector<Location> path = {Location::PARIS, Location::AMSTERDAM, Location::LONDRES, Location::PARIS, Location::NEWYORK};
    vector<Location> path = {Location::PARIS, Location::LONDRES};

    for(int i = 0; i < nbPlanes; i ++) {
        for (int j = 0; j < nbParts; j ++) {
            planeParts.push_back(PlanePart());
        }
        A.push_back(Plane(path, planeParts, 0, 0, i));
        planeParts.clear();
    }
}


User::User(const vector<Plane> &A) : A(A) {}


vector<Plane> User::getPlanes() {
    return A;

}


void User::addPlane(const Plane p) {
    A.push_back(p);
}


double User::findCost() {
    double finalCost = 0.;
    map<Plane,pair<vector<bool>,double>> valeurs_actions;
    for(int i = 0; i < A.size(); i ++) {
        finalCost += A[i].findValue(valeurs_actions, A).first;
    }

    return finalCost;
}