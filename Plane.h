#ifndef PROJET_Plane_H
#define PROJET_Plane_H

#include "Location.h"
#include "PlanePart.h"
#include <tuple>
#include <iostream>
#include <vector>

using namespace std;

class Plane {
    const int breakdown = 1000000;
    const int T = 10;
    Location location;
    vector<PlanePart> planeParts;
    int time;
public:
    Plane(Location location, const vector<PlanePart> &planePart, int time);

    // On retourne dans l'ordre la probabilité d'obtenir l'avion, l'avion, et le coût associé
    vector<tuple<double, Plane, double>> nextPlanesPossible(vector<bool> action) const;

    pair<double, vector<bool>> findValue(map<Plane, pair<vector<bool>,double>> &valeurs_actions) const;

    bool operator<(const Plane &plane) const {
        return (time < plane.time || (time == plane.time && planeParts < plane.planeParts) ||
                (time == plane.time && planeParts == plane.planeParts && location < plane.location));
    }
};

double meanValue(const vector<tuple<double, Plane, double>> &PlanesWithProba, map<Plane,pair<vector<bool>, double>> &valeurs_actions);

vector<bool> genere(int i, int size);

#endif //PROJET_Plane_H
