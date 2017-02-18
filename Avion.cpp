#include "Avion.h"

Avion::Avion(Location location, const Piece &piece, int temps) : location(location), piece(piece),
                                                                              temps(temps) {}


vector<tuple<double, Avion, double>> Avion::nextAvionsPossibles(bool action) const {
    vector<tuple<double, Avion, double>> avionsAvecProba;
    vector<pair<double, Piece>> pieceAvecProba = piece.nextPiecePossible(action);

    for (int i = 0; i < pieceAvecProba.size(); i ++) {
        // Cas de la panne
        if (pieceAvecProba[i].second.depasseSeuil()) {
            avionsAvecProba.push_back(tuple<double, Avion, double>(pieceAvecProba[i].first,
                                                         Avion(location, Piece(), temps + 1), Panne));
        }
        else {
            avionsAvecProba.push_back(tuple<double, Avion, double>(pieceAvecProba[i].first,
                                                         Avion(otherLocation(location), pieceAvecProba[i].second,
                                                              temps + 1), (int) location * action));
        }
    }
    return avionsAvecProba;
}


pair<double, bool> Avion::trouveValeur(map<Avion,int> &valeurs) const {
    if (temps == T) {
        // Que mettre en valeur de retour dans ce cas ?
        return pair<double, bool>(0, false);
    }
    else {
        double meilleureValeur = 0;
        map<Avion,int>::iterator it;
        it = valeurs.find(*this);
        if (it != valeurs.end()) {
             meilleureValeur = (*it).second;
        }
        else {
            double valeurAvecChangementPiece = 0;
            double valeurSansChangementPiece = 0;
            // Cas du changement de la pièce
            vector<tuple<double, Avion, double>> avionsAvecProba1 = nextAvionsPossibles(true);
            for (int i = 0; i < avionsAvecProba1.size(); i ++) {
                valeurAvecChangementPiece += get<0>(avionsAvecProba1[i]) *
                        (get<1>(avionsAvecProba1[i]).trouveValeur(valeurs).first + get<2>(avionsAvecProba1[i]));
            }

            // Cas où l'on ne change pas la pièce
            vector<tuple<double, Avion, double>> avionsAvecProba2 = nextAvionsPossibles(false);
            for (int i = 0; i < avionsAvecProba2.size(); i ++) {
                valeurSansChangementPiece += get<0>(avionsAvecProba2[i]) *
                        (get<1>(avionsAvecProba2[i]).trouveValeur(valeurs).first + get<2>(avionsAvecProba2[i]));
            }
            meilleureValeur = min(valeurAvecChangementPiece, valeurSansChangementPiece);
            valeurs.insert(pair<Avion,int>(*this,meilleureValeur));
        }
        return pair<double, bool>(meilleureValeur, true);
    }
}

