#include "Piece.h"
#include <iostream>
using namespace std;

Piece::Piece() {
    frequence = 0;
    whichPente = false;
}

Piece::Piece(double frequence, bool whichPente) {
    this->frequence = frequence;
    this->whichPente = whichPente;
}

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

    // Cas où l'on change la pièce
    else {
        // La fréquence est remise à 0 mais un vol est tout de même effectué
        // On reste sur la pente basse...
        pieceAvecProba.push_back(pair<double,Piece>(probaP0, Piece(pente0, false)));
        // ... ou on bascule sur la pente haute
        pieceAvecProba.push_back(pair<double,Piece>(1 - probaP0, Piece(pente1, true)));
    }

    return pieceAvecProba;
}


double Piece::calcul_cout_aux(int temps, int retard, double probabilite, double cout, const vector<bool> &maintenances, const Avion &a) {
     if (temps == T) {
         return (probabilite * cout);
     }
     else {
        vector<tuple<double,Piece,double,int>> pieces_suivantes = (*this).pieces_suivantes(maintenances[temps-retard], retard, temps, a);
        double valeur = 0;
        for (int k = 0; k < pieces_suivantes.size(); ++k) {
            valeur += get<1>(pieces_suivantes[k]).calcul_cout_aux(temps+1, get<3>(pieces_suivantes[k]), get<0>(pieces_suivantes[k]) * probabilite, cout + get<2>(pieces_suivantes[k]), maintenances, a);
        }
     }
 }


vector<tuple<double,Piece,double,int>> Piece::pieces_suivantes(bool action, int retard, int temps, const Avion &a) {
    vector<tuple<double,Piece,double,int>> pieces_suiv;
    vector<pair<double,Piece>> pieces = (*this).nextPiecePossible(action);
    for (int k = 0; k < pieces.size(); ++k) {
        // Cas de la panne : l'avion bloqué est remplacé directement par un nouvel avion avec une pièce neuve qui effectue le trajet prévu
        if (pieces[k].second.depasseSeuil()) {
            pieces_suiv.push_back(tuple<double,Piece,double,int>(pieces[k].first, Piece(), 10000000000000 + ((int) a.trouve_position(temps-retard))*action, retard+1));
        }
        else {
            pieces_suiv.push_back(tuple<double,Piece,double,int>(pieces[k].first, pieces[k].second, ((int) a.trouve_position(temps-retard))*action, retard));
        }
    }
    return pieces_suiv;
}
