#ifndef PROJECT_LIGNE_H
#define PROJECT_LIGNE_H

#include <random>
#include <cstdlib>
#include <vector>
#include <utility>
#include <map>
#include "Lieu.h"
#include "Avion.h"
#include "Piece.h"
using namespace std;

class Ligne{
    int l;  // l écrit en base 2 représente le programme des maintenances
    Avion avion;
public:
    Ligne(int programme_maintenances, const Avion &a){
        l = programme_maintenances;
        avion=Avion(a);
    }
    bool operator<(const Ligne &ligne) const {
        return (l < ligne.l || (l == ligne.l && avion < ligne.avion) );
    }
    double calcul_cout();
};




void decomposition_binaire(int n, vector<bool> &v);


#endif
