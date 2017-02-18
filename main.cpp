#include "Avion.h"
#include <iostream>

using namespace std;


int main(){
    Avion avion(Location::HUB, Piece(), 0);
    map<Avion,pair<int,double>> valeurs_actions;
    cout << avion.trouveValeur(valeurs_actions).first << endl;

    return 0;
}
