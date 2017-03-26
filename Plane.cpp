#include "Plane.h"

Plane::Plane(vector<Location> path, const vector<PlanePart> &planeParts, int time, int place, int id) : path(path),
                                                                                 planeParts(planeParts), time(time), place(place), id(id) {}



vector<tuple<double, Plane, double>> Plane::nextPlanesPossible(vector<bool> action, vector<Plane> planes) const {
    vector<tuple<double, Plane, double>> PlanesWithProba;
    vector<vector<pair<double, PlanePart>>> nextStatesForParts;

    vector<int> multiplierOfPossibleStates;
    for (int i = 0; i < planeParts.size(); i ++) {
        nextStatesForParts.push_back(planeParts[i].nextPlanePartPossible(action[i]));
        multiplierOfPossibleStates.push_back(nextStatesForParts[i].size());
    }

    for (int i = multiplierOfPossibleStates.size() - 2; i >= 0; i --) {
        multiplierOfPossibleStates[i] *= multiplierOfPossibleStates[i + 1];
    }
    multiplierOfPossibleStates.push_back(1);

    vector<pair<double, vector<PlanePart>>> planePartWithProba;
    for (int i = 0; i < multiplierOfPossibleStates[0]; i ++) {
        planePartWithProba.push_back(pair<double, vector<PlanePart>>(1,vector<PlanePart>()));
    }


    for (int i = 0; i < planeParts.size(); i ++) {
        for (int j = 0; j < multiplierOfPossibleStates[0] / multiplierOfPossibleStates[i + 1]; j ++) {
            for (int k = 0; k < multiplierOfPossibleStates[i + 1]; k ++) {
                planePartWithProba[j * multiplierOfPossibleStates[i + 1] + k].first *= nextStatesForParts[i][j%(multiplierOfPossibleStates[i]/multiplierOfPossibleStates[i + 1])].first;
                planePartWithProba[j * multiplierOfPossibleStates[i + 1] + k].second.push_back(nextStatesForParts[i][j%(multiplierOfPossibleStates[i]/multiplierOfPossibleStates[i + 1])].second);
            }
        }
    }

    for (int i = 0; i < planePartWithProba.size(); i ++) {
        int totalCost = 0;
        bool breakDown = false;
        for (int j = 0; j < planePartWithProba[i].second.size(); j ++) {
            // Cas de breakDown sur une pièce
            if (planePartWithProba[i].second[j].overBound()) {
                planePartWithProba[i].second[j].reinitialize();
                totalCost += breakdown;
                breakDown = true;
            }
            else {
                totalCost += (int) path[place % path.size()] * action[j];
            }
        }

        for (int k = 0; k < planes.size(); k ++) {
            map<Plane, pair<vector<bool>, double>> valeurs_actions;
            // Récursivité qui ne marche pas : if (planes[k].getId() != id && planes[k].getPlace() == place && prod(action) & prod(planes[k].findValue(valeurs_actions, planes).second)) {
            if (planes[k].getId() != id && planes[k].getPlace() == place && prod(action)) {
                totalCost += planeCorrelation;
            }
        }

        int nextPlace = place;
        // Pas de Panne
        if (!breakDown) {
            nextPlace += 1;
        }

        PlanesWithProba.push_back(tuple<double, Plane, double>(planePartWithProba[i].first,
                                                    Plane(path, planePartWithProba[i].second, time + 1, nextPlace, id),
                                                               totalCost));
    }
    return PlanesWithProba;
}



// dans le vecteur actions, on retient à l'indice t le choix à faire à la date t permettant d'atteindre le cout minimum renvoyé par la fonction
pair<double, vector<bool>> Plane::findValue(map<Plane, pair<vector<bool>, double>> &valeurs_actions, vector<Plane> planes) const {
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
            action = base10to2(0, planeParts.size());
            vector<tuple<double, Plane, double>> PlanesWithProba = nextPlanesPossible(action, planes);
            // Faut-il mettre ici la condition de corrélation entre la maintenance de 2 avions ?
            bestValue = meanValue(PlanesWithProba, valeurs_actions, planes);

            for (int i = 1; i < pow(2, planeParts.size()); i ++) {
                vector<bool> actionPossible = base10to2(i, planeParts.size());
                PlanesWithProba = nextPlanesPossible(actionPossible, planes);
                double valeur = meanValue(PlanesWithProba, valeurs_actions, planes);

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

double meanValue(const vector<tuple<double, Plane, double>> &PlanesWithProba, map<Plane,pair<vector<bool>, double>> &valeurs_actions,
vector<Plane> planes) {
    double valeur = 0;
    for (int i = 0; i < PlanesWithProba.size(); i ++) {
        valeur += get<0>(PlanesWithProba[i]) *
                                     (get<1>(PlanesWithProba[i]).findValue(valeurs_actions, planes).first + get<2>(PlanesWithProba[i]));
    }
    return valeur;
}

// Passe l'entier qui est en base 10 en base 2, en renvoyant un tableau de taille size
vector<bool> base10to2(int integer, int size) {

    vector<bool> vector01;
    while (integer != 0) {
        vector01.push_back((bool) (integer % 2));
        integer = (integer - integer % 2) / 2;
    }

    while (vector01.size() != size) {
        vector01.push_back(false);
    }
    return vector01;
}

bool prod(vector<bool> action) {
    /* Fonction qui renvoie True si l'action contient au moins une maintenance */
    for (int i = 0; i < action.size(); i ++) {
        if (action[i]) {
            return true;
        }
    }
    return false;
}