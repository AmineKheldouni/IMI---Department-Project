#include <iostream>
#include <vector>
using namespace std;
#include "Ligne.h"

void decomposition_binaire(int n, vector<bool> &v){
    int compteur = 0;
    while (n != 0){
        v.push_back(n%2);
        n=int(n/2);
        ++compteur;
    }
    for (int k = compteur; k < T; ++k) {
        v.push_back(0);
    }

}


double Ligne::calcul_cout(){
    Piece piece(0,0);
    int temps = 0;
    vector<bool> maintenances;
    decomposition_binaire(l, maintenances);
    int retard = 0;
    piece.calcul_cout_aux(temps, 0, 1, 0, maintenances, avion);
}
