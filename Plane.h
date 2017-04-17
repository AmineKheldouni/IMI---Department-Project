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
    int T;
    vector<Location> path;
    vector<PlanePart> planeParts;
    int time;
    int place;
public:
    Plane(vector<Location> path, const vector<PlanePart> &planePart, int time, int place, int T);

    // On retourne dans l'ordre la probabilité d'obtenir l'avion, l'avion, et le coût associé
    vector<tuple<double, Plane, double>> nextPlanesPossible(vector<bool> action) const;

    pair<double, vector<bool>> findValue(map<Plane, pair<vector<bool>,double>> &valeurs_actions) const;

    bool operator<(const Plane &plane) const {
        return (T - time < plane.T - plane.time || (T - time == plane.T - plane.time && planeParts < plane.planeParts) ||
                (T - time == plane.T - plane.time && planeParts == plane.planeParts && place < plane.place));
    }

    int next(vector<bool> action);
};

double meanValue(const vector<tuple<double, Plane, double>> &PlanesWithProba, map<Plane,pair<vector<bool>, double>> &valeurs_actions);

vector<bool> base10to2(int integer, int size);

#endif //PROJET_Plane_H
