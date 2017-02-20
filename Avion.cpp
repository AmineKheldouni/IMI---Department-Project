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
pair<double, bool> Avion::trouveValeur(map<Avion,pair<bool, double>> &valeurs_actions) const {
    if (temps == T) {
        // Que mettre en valeur de retour dans ce cas ?
        return pair<double, bool>(0, false);
    }
    else {
        double meilleureValeur;
        bool action;
        map<Avion, pair<bool, double>>::iterator it;
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
            valeurAvecChangementPiece = esperanceValeur(avionsAvecProba1, valeurs_actions);

            // Cas où l'on ne change pas la pièce
            vector<tuple<double, Avion, double>> avionsAvecProba2 = nextAvionsPossibles(false);
            valeurSansChangementPiece = esperanceValeur(avionsAvecProba2, valeurs_actions);

            meilleureValeur = min(valeurAvecChangementPiece, valeurSansChangementPiece);
            action = (min(valeurAvecChangementPiece, valeurSansChangementPiece) == valeurAvecChangementPiece);
            valeurs_actions.insert(pair<Avion,pair<bool, double>>(*this,pair<int,double> (action, meilleureValeur)));
        }
        return pair<double, bool>(meilleureValeur, action);
    }
}

double esperanceValeur(const vector<tuple<double, Avion, double>> &avionsAvecProba, map<Avion,pair<bool, double>> &valeurs_actions) {
    double valeur = 0;
    for (int i = 0; i < avionsAvecProba.size(); i ++) {
        valeur += get<0>(avionsAvecProba[i]) *
                                     (get<1>(avionsAvecProba[i]).trouveValeur(valeurs_actions).first + get<2>(avionsAvecProba[i]));
    }
    return valeur;
}