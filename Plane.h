#include "Location.h"
#include "PlanePart.h"
#include <tuple>
#include <iostream>
#include <vector>

using namespace std;

class Plane {
    const int breakdown = 1000000;
    const int T = 100;
    vector<Location> path;

    int time;
    int place;
public:
    Plane(vector<Location> path, const vector<PlanePart> &planePart, int time, int place);
    vector<PlanePart> planeParts;
    // On retourne dans l'ordre la probabilité d'obtenir l'avion, l'avion, et le coût associé
    vector<tuple<double, Plane, double>> nextPlanesPossible(vector<bool> action) const;

    pair<double, vector<bool>> findValue(map<Plane, pair<vector<bool>,double>> &valeurs_actions) const;

    bool operator<(const Plane &plane) const {
        return (time < plane.time || (time == plane.time && planeParts < plane.planeParts) ||
                (time == plane.time && planeParts == plane.planeParts && place < plane.place));
    }
};

double meanValue(const vector<tuple<double, Plane, double>> &PlanesWithProba, map<Plane,pair<vector<bool>, double>> &valeurs_actions);

vector<bool> base10to2(int integer, int size);
double meanCost(int T, int nb_part, int change);
double meanCost2(int T, int nb_part, int change);
