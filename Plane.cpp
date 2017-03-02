#include "Plane.h"

Plane::Plane(Location location, const vector<PlanePart> &planeParts, int time) : location(location),
                                                                                 planeParts(planeParts), time(time) {}



vector<tuple<double, Plane, double>> Plane::nextPlanesPossible(vector<bool> action) const {
    vector<tuple<double, Plane, double>> PlanesWithProba;
    vector<vector<pair<double, PlanePart>>> planePartWithProba2;

    vector<int> compteur;
    for (int i = 0; i < planeParts.size(); i ++) {
        planePartWithProba2.push_back(planeParts[i].nextPlanePartPossible(action[i]));
        compteur.push_back(planePartWithProba2[i].size());
    }

    for (int i = compteur.size() - 2; i >= 0; i --) {
        compteur[i] *= compteur[i + 1];
    }
    compteur.push_back(1);

    vector<pair<double, vector<PlanePart>>> planePartWithProba;
    for (int i = 0; i < compteur[0]; i ++) {
        planePartWithProba.push_back(pair<double, vector<PlanePart>>(1,vector<PlanePart>()));
    }


    for (int i = 0; i < planeParts.size(); i ++) {
        for (int j = 0; j < compteur[0] / compteur[i + 1]; j ++) {
            for (int k = 0; k < compteur[i + 1]; k ++) {
                planePartWithProba[j * compteur[i + 1] + k].first *= planePartWithProba2[i][j%(compteur[i]/compteur[i + 1])].first;
                planePartWithProba[j * compteur[i + 1] + k].second.push_back(planePartWithProba2[i][j%(compteur[i]/compteur[i + 1])].second);
            }
        }
    }

    for (int i = 0; i < planePartWithProba.size(); i ++) {
        int coutTotal = 0;
        bool panne = false;
        for (int j = 0; j < planePartWithProba[i].second.size(); j ++) {
            // Cas de panne sur une pièce
            if (planePartWithProba[i].second[j].overBound()) {
                planePartWithProba[i].second[j].reinitialize();
                coutTotal += breakdown;
                panne = true;
            }
            else {
                coutTotal += (int) location * action[j];
            }
        }

        Location nextLocation = location;
        // Pas de Panne
        if (!panne) {
            nextLocation = otherLocation(location);
        }

        PlanesWithProba.push_back(tuple<double, Plane, double>(planePartWithProba[i].first,
                                                    Plane(nextLocation, planePartWithProba[i].second, time + 1),
                                                               coutTotal));
    }
    return PlanesWithProba;
}



// dans le vecteur actions, on retient à l'indice t le choix à faire à la date t permettant d'atteindre le cout minimum renvoyé par la fonction
pair<double, vector<bool>> Plane::findValue(map<Plane,pair<vector<bool>, double>> &valeurs_actions) const {
    if (time == T) {
        // Que mettre en valeur de retour dans ce cas ?
        return pair<double, vector<bool>>(0, vector<bool>());
    }
    else {
        double bestValue;
        vector<bool> action;
        map<Plane, pair<vector<bool>, double>>::iterator it;
        it = valeurs_actions.find(*this);
        if (it != valeurs_actions.end()) {
             bestValue = ((*it).second).second;
             action = ((*it).second).first;
        }
        else {

            action = genere(0, planeParts.size());
            vector<tuple<double, Plane, double>> PlanesWithProba = nextPlanesPossible(action);
            bestValue = meanValue(PlanesWithProba, valeurs_actions);

            for (int i = 1; i < pow(2, planeParts.size()); i ++) {
                vector<bool> actionPossible = genere(i, planeParts.size());
                PlanesWithProba = nextPlanesPossible(actionPossible);
                double valeur = meanValue(PlanesWithProba, valeurs_actions);

                if (valeur < bestValue) {
                    bestValue = valeur;
                    action = actionPossible;
                }
            }


            valeurs_actions.insert(pair<Plane,pair<vector<bool>, double>>(*this,pair<vector<bool>,double> (action, bestValue)));
        }
        return pair<double, vector<bool>>(bestValue, action);
    }
}

double meanValue(const vector<tuple<double, Plane, double>> &PlanesWithProba, map<Plane,pair<vector<bool>, double>> &valeurs_actions) {
    double valeur = 0;
    for (int i = 0; i < PlanesWithProba.size(); i ++) {
        valeur += get<0>(PlanesWithProba[i]) *
                                     (get<1>(PlanesWithProba[i]).findValue(valeurs_actions).first + get<2>(PlanesWithProba[i]));
    }
    return valeur;
}

vector<bool> genere(int i, int size) {

    vector<bool> retour;
    while (i != 0) {
        retour.push_back((bool) (i % 2));
        i = (i - i % 2) / 2;
    }

    while (retour.size() != size) {
        retour.push_back(false);
    }
    return retour;
}