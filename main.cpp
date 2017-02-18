#include "Avion.h"
#include <iostream>

using namespace std;


int main(){
    Avion avion(Location::HUB, Piece(), 0);
    cout << avion.trouveValeur().first << endl;
    return 0;
}
