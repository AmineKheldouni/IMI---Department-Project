#include "Avion.h"
#include <iostream>

using namespace std;


int main(){
    Avion avion(Location::HUB, Piece(), 0);
    map<Avion,int> valeur;
    cout << avion.trouveValeur(valeur).first << endl;
    return 0;
}
