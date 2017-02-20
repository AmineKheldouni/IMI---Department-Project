#include "Plane.h"

Plane::Plane(Location location, const PlanePart &planePart, int time) : location(location), planePart(planePart),
                                                                              time(time) {}


vector<tuple<double, Plane, double>> Plane::nextPlanesPossible(bool action) const {
    vector<tuple<double, Plane, double>> PlanesWithProba;
    vector<pair<double, PlanePart>> planePartWithProba = planePart.nextPlanePartPossible(action);

    for (int i = 0; i < planePartWithProba.size(); i ++) {
        // Cas de la panne
        if (planePartWithProba[i].second.overBound()) {
            PlanesWithProba.push_back(tuple<double, Plane, double>(planePartWithProba[i].first,
                                                         Plane(location, PlanePart(), time + 1), breakdown));
        }
        else {
            PlanesWithProba.push_back(tuple<double, Plane, double>(planePartWithProba[i].first,
                                                         Plane(otherLocation(location), planePartWithProba[i].second,
                                                              time + 1), (int) location * action));
        }
    }
    return PlanesWithProba;
}



// dans le vecteur actions, on retient à l'indice t le choix à faire à la date t permettant d'atteindre le cout minimum renvoyé par la fonction
pair<double, bool> Plane::findValue(map<Plane,pair<bool, double>> &valeurs_actions) const {
    if (time == T) {
        // Que mettre en valeur de retour dans ce cas ?
        return pair<double, bool>(0, false);
    }
    else {
        double bestValue;
        bool action;
        map<Plane, pair<bool, double>>::iterator it;
        it = valeurs_actions.find(*this);
        if (it != valeurs_actions.end()) {
             bestValue = ((*it).second).second;
             action = ((*it).second).first;
        }
        else {
            double valeurWithChangePlanePart = 0;
            double valeurWithoutChangePlanePart = 0;

            // Cas du Change de la pièce
            vector<tuple<double, Plane, double>> PlanesWithProba1 = nextPlanesPossible(true);
            valeurWithChangePlanePart = meanValue(PlanesWithProba1, valeurs_actions);

            // Cas où l'on ne change pas la pièce
            vector<tuple<double, Plane, double>> PlanesWithProba2 = nextPlanesPossible(false);
            valeurWithoutChangePlanePart = meanValue(PlanesWithProba2, valeurs_actions);

            bestValue = min(valeurWithChangePlanePart, valeurWithoutChangePlanePart);
            action = (min(valeurWithChangePlanePart, valeurWithoutChangePlanePart) == valeurWithChangePlanePart);
            valeurs_actions.insert(pair<Plane,pair<bool, double>>(*this,pair<int,double> (action, bestValue)));
        }
        return pair<double, bool>(bestValue, action);
    }
}

double meanValue(const vector<tuple<double, Plane, double>> &PlanesWithProba, map<Plane,pair<bool, double>> &valeurs_actions) {
    double valeur = 0;
    for (int i = 0; i < PlanesWithProba.size(); i ++) {
        valeur += get<0>(PlanesWithProba[i]) *
                                     (get<1>(PlanesWithProba[i]).findValue(valeurs_actions).first + get<2>(PlanesWithProba[i]));
    }
    return valeur;
}