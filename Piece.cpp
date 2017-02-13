#include "Piece.h"

#include <cmath>
#include <iostream>

using namespace std;

Piece::Piece() {
    frequence = 0;
    whichPente = false;
}

void Piece::Next(bool action) {
    if (!action) {
        if (whichPente) {
            frequence += pente1;
        }
        else {
            double transition = rand() / RAND_MAX;
            if (transition > probaP0) {
                frequence += pente1;
                whichPente = true;
            }
            else {
                frequence += pente0;
            }
        }
    }
    else {
        frequence = 0;
        whichPente = false;
    }
}
