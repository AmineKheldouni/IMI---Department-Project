#include "PlanePart.h"
#include <iostream>

using namespace std;

PlanePart::PlanePart() {
    frequency = 0;
    whichPente = false;
}

PlanePart::PlanePart(double frequency, bool whichPente) : frequency(frequency), whichPente(whichPente) {}

bool PlanePart::overBound() const {
    return (frequency > seuil);
}

// Pas maintenable facilement car ~duplication de code
// Mais à garder car peut être utile pour de meilleures performances
/*
void PlanePart::next(bool action) {
    // Cas où on ne change pas la pièce
    if (!action) {
        if (whichPente) {
            frequency += pente1;
        }
        else {
            double transition = (double) rand() / RAND_MAX;
            if (transition > probaP0) {
                frequency += pente1;
                whichPente = true;
            }
            else {
                frequency += pente0;
            }
        }
    }
    // Cas où on change la pièce
    else {
        frequency = 0;
        whichPente = false;
    }
}
*/

void PlanePart::next(bool action) {
    vector<pair<double,PlanePart>> PlanePartWithProba = nextPlanePartPossible(action);
    double probaChoice = (double) rand() / RAND_MAX;

    // On boucle sur toute les pièces du vecteur pour déterminer laquelle on choisit
    for (int i = 0; i < PlanePartWithProba.size(); i ++) {
        if (probaChoice - PlanePartWithProba[i].first > 0) {
            probaChoice -= PlanePartWithProba[i].first;
        }
        else {
            frequency = PlanePartWithProba[i].second.frequency;
            whichPente = PlanePartWithProba[i].second.whichPente;
            return;
        }
    }
}


vector<pair<double,PlanePart>> PlanePart::nextPlanePartPossible(bool action) const {
    vector<pair<double,PlanePart>> PlanePartWithProba;

    // Cas où on ne change pas la pièce
    if (!action) {
        // Cas où l'on est sur la pente haute
        if (whichPente) {
            PlanePartWithProba.push_back(pair<double,PlanePart>(1, PlanePart(frequency + pente1, whichPente)));
        }
        // Cas où l'on est sur la pente basse
        else {
            // On reste sur la pente basse...
            PlanePartWithProba.push_back(pair<double,PlanePart>(probaP0, PlanePart(frequency + pente0, false)));
            // ... ou on bascule sur la pente haute
            PlanePartWithProba.push_back(pair<double,PlanePart>(1 - probaP0, PlanePart(frequency + pente1, true)));
        }
    }

    // Cas où l'n change la pièce
    else {
        // La fréquence est remise à 0 mais un vol est tout de même effectué
        // On reste sur la pente basse...
        PlanePartWithProba.push_back(pair<double,PlanePart>(probaP0, PlanePart(pente0, false)));
        // ... ou on bascule sur la pente haute
        PlanePartWithProba.push_back(pair<double,PlanePart>(1 - probaP0, PlanePart(pente1, true)));
    }

    return PlanePartWithProba;
}
