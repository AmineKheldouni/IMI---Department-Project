#include "Piece.h"
#include <iostream>

using namespace std;

Piece::Piece() {
    frequence = 0;
    whichPente = false;
}

Piece::Piece(double frequence, bool whichPente) : frequence(frequence), whichPente(whichPente) {}

bool Piece::depasseSeuil() const {
    return (frequence > seuil);
}

// Pas maintenable facilement car ~duplication de code
// Mais à garder car peut être utile pour de meilleures performances
/*
void Piece::next(bool action) {
    // Cas où on ne change pas la pièce
    if (!action) {
        if (whichPente) {
            frequence += pente1;
        }
        else {
            double transition = (double) rand() / RAND_MAX;
            if (transition > probaP0) {
                frequence += pente1;
                whichPente = true;
            }
            else {
                frequence += pente0;
            }
        }
    }
    // Cas où on change la pièce
    else {
        frequence = 0;
        whichPente = false;
    }
}
*/

void Piece::next(bool action) {
    vector<pair<double,Piece>> pieceAvecProba = nextPiecePossible(action);
    double probaDeChoix = (double) rand() / RAND_MAX;

    // On boucle sur toute les pièces du vecteur pour déterminer laquelle on choisit
    for (int i = 0; i < pieceAvecProba.size(); i ++) {
        if (probaDeChoix - pieceAvecProba[i].first > 0) {
            probaDeChoix -= pieceAvecProba[i].first;
        }
        else {
            frequence = pieceAvecProba[i].second.frequence;
            whichPente = pieceAvecProba[i].second.whichPente;
            return;
        }
    }
}


vector<pair<double,Piece>> Piece::nextPiecePossible(bool action) const {
    vector<pair<double,Piece>> pieceAvecProba;

    // Cas où on ne change pas la pièce
    if (!action) {
        // Cas où l'on est sur la pente haute
        if (whichPente) {
            pieceAvecProba.push_back(pair<double,Piece>(1, Piece(frequence + pente1, whichPente)));
        }
        // Cas où l'on est sur la pente basse
        else {
            // On reste sur la pente basse...
            pieceAvecProba.push_back(pair<double,Piece>(probaP0, Piece(frequence + pente0, false)));
            // ... ou on bascule sur la pente haute
            pieceAvecProba.push_back(pair<double,Piece>(1 - probaP0, Piece(frequence + pente1, true)));
        }
    }

    // Cas où l'n change la pièce
    else {
        // La fréquence est remise à 0 mais un vol est tout de même effectué
        // On reste sur la pente basse...
        pieceAvecProba.push_back(pair<double,Piece>(probaP0, Piece(pente0, false)));
        // ... ou on bascule sur la pente haute
        pieceAvecProba.push_back(pair<double,Piece>(1 - probaP0, Piece(pente1, true)));
    }

    return pieceAvecProba;
}
