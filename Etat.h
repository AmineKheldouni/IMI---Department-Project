#ifndef PROJET_ETAT_H
#define PROJET_ETAT_H

#include "Location.h"
#include "Piece.h"

class Etat {
    Location location;
    Piece piece;
    int temps;
    double valeur;
public:
    Etat(Location location, const Piece &piece, int temps, double valeur);

    
};

#endif //PROJET_ETAT_H
