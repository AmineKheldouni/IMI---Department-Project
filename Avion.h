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
    Location location;
    Piece piece;
    int temps;
public:
    Avion(Location location, const Piece &piece, int temps);

    // On retourne dans l'ordre la probabilité d'obtenir l'avion, l'avion, et le coût associé
    vector<tuple<double, Avion, double>> nextAvionsPossibles(bool action) const;

    pair<double, bool> trouveValeur(map<Avion, pair<bool,double>> &valeurs_actions) const;

    bool operator<(const Avion &avion) const {
        return (temps < avion.temps || (temps == avion.temps && piece < avion.piece) ||
                (temps == avion.temps && piece == avion.piece && location < avion.location));
    }
};

double esperanceValeur(const vector<tuple<double, Avion, double>> &avionsAvecProba, map<Avion,pair<bool, double>> &valeurs_actions);

#endif //PROJET_AVION_H
