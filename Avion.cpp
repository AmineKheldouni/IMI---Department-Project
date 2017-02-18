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



// dans le vecteur actions, on retient à l'indice t le choix à faire à la date t permettant d'atteindre le cout minimum renvoyé par la fonction
pair<double, bool> Avion::trouveValeur(map<Avion,pair<int,double>> &valeurs_actions) const {
    if (temps == T) {
        // Que mettre en valeur de retour dans ce cas ?
        return pair<double, bool>(0, false);
    }
    else {
        double meilleureValeur = 0;
        int action = false;
        map<Avion, pair<int,double>>::iterator it;
        it = valeurs_actions.find(*this);
        if (it != valeurs_actions.end()) {
             meilleureValeur = ((*it).second).second;
             action = ((*it).second).first;
        }
        else {
            double valeurAvecChangementPiece = 0;
            double valeurSansChangementPiece = 0;
            // Cas du changement de la pièce
            vector<tuple<double, Avion, double>> avionsAvecProba1 = nextAvionsPossibles(true);
            for (int i = 0; i < avionsAvecProba1.size(); i ++) {
                valeurAvecChangementPiece += get<0>(avionsAvecProba1[i]) *
                        (get<1>(avionsAvecProba1[i]).trouveValeur(valeurs_actions).first + get<2>(avionsAvecProba1[i]));
            }

            // Cas où l'on ne change pas la pièce
            vector<tuple<double, Avion, double>> avionsAvecProba2 = nextAvionsPossibles(false);
            for (int i = 0; i < avionsAvecProba2.size(); i ++) {
                valeurSansChangementPiece += get<0>(avionsAvecProba2[i]) *
                        (get<1>(avionsAvecProba2[i]).trouveValeur(valeurs_actions).first + get<2>(avionsAvecProba2[i]));
            }
            meilleureValeur = min(valeurAvecChangementPiece, valeurSansChangementPiece);
            action = (min(valeurAvecChangementPiece, valeurSansChangementPiece) == valeurAvecChangementPiece);
            valeurs_actions.insert(pair<Avion,pair<int,double>>(*this,pair<int,double> (action, meilleureValeur)));
        }
        return pair<double, bool>(meilleureValeur, action);
    }
}
