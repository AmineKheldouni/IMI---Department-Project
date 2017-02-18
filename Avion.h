#ifndef PROJET_AVION_H
#define PROJET_AVION_H

#include "Location.h"
#include "Piece.h"
#include <tuple>
#include <iostream>

using namespace std;

class Avion {
    const int Panne = 1000000;
    const int T = 12;
    Location location;
    Piece piece;
    int temps;
public:
    Avion(Location location, const Piece &piece, int temps);

    // On retourne dans l'ordre la probabilité d'obtenir l'avion, l'avion, et le coût associé
    vector<tuple<double, Avion, double>> nextAvionsPossibles(bool action) const;

    pair<double, bool> trouveValeur(map<Avion, int> &valeurs) const;

    bool operator<(const Avion avion) const {
        return (temps < avion.temps || (temps == avion.temps && piece < avion.piece) ||
                (temps == avion.temps && piece == avion.piece && location < avion.location));
    }
};

#endif //PROJET_AVION_H
