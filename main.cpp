#include "Avion.h"
#include <iostream>
#include <ostream>

using namespace std;


int main(){
    vector<Location> trajet = {Location::PARIS, Location::AMSTERDAM, Location::LONDRES, Location::PARIS, Location::NEWYORK};
    Avion avion(trajet, Piece(), 0, 0);
    map<Avion,pair<bool,double>> valeurs_actions;
    cout << avion.trouveValeur(valeurs_actions).first << endl;

    return 0;
}
