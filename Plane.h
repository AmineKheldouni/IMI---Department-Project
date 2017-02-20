#ifndef PROJET_Plane_H
#define PROJET_Plane_H

#include "Location.h"
#include "PlanePart.h"
#include <tuple>
#include <iostream>

using namespace std;

class Plane {
    const int breakdown = 1000000;
    const int T = 10;
    Location location;
    PlanePart planePart;
    int time;
public:
    Plane(Location location, const PlanePart &PlanePart, int time);

    // On retourne dans l'ordre la probabilité d'obtenir l'Plane, l'Plane, et le coût associé
    vector<tuple<double, Plane, double>> nextPlanesPossible(bool action) const;

    pair<double, bool> findValue(map<Plane, pair<bool,double>> &valeurs_actions) const;

    bool operator<(const Plane &Plane) const {
        return (time < Plane.time || (time == Plane.time && planePart < Plane.planePart) ||
                (time == Plane.time && planePart == Plane.planePart && location < Plane.location));
    }
};

double meanValue(const vector<tuple<double, Plane, double>> &PlanesWithProba, map<Plane,pair<bool, double>> &valeurs_actions);

#endif //PROJET_Plane_H
