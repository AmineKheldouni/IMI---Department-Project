#ifndef PROJET_AVION_H
#define PROJET_AVION_H

#include "Location.h"
#include "Piece.h"
#include <tuple>
#include <iostream>

using namespace std;

class Avion {
    const int Panne = 1000000;
    const int T = 10;
    const vector<Location> trajet;
    Piece piece;
    int temps;
    int position;
public:
    Avion(const vector<Location> &trajet, const Piece &piece, int temps, int position);

    // On retourne dans l'ordre la probabilité d'obtenir l'avion, l'avion, et le coût associé
    vector<tuple<double, Avion, double>> nextAvionsPossibles(bool action) const;

    pair<double, bool> trouveValeur(map<Avion, pair<bool,double>> &valeurs_actions) const;

    bool operator<(const Avion &avion) const {
        return (temps < avion.temps || (temps == avion.temps && piece < avion.piece) ||
                (temps == avion.temps && piece == avion.piece && position < avion.position));
    }
};

double esperanceValeur(const vector<tuple<double, Avion, double>> &avionsAvecProba, map<Avion,pair<bool, double>> &valeurs_actions);

#endif //PROJET_AVION_H
