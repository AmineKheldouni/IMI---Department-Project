
#ifndef PIECE_H
#define PIECE_H

#include <random>
#include <cstdlib>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class Piece
{
    // Il FAUT que pente0 < pente1 < seuil
    const double pente0 = 0.1;
    const double pente1 = 1;
    const double seuil = 3;
    const double probaP0 = 0.9;
    double frequence;
    bool whichPente;

public :
    Piece();

    Piece(double frequence, bool whichPente);

    bool depasseSeuil() const;

    void next(bool action);

    // On retourne la pièce et la probabilité de l'obtenir
    vector<pair<double,Piece>> nextPiecePossible(bool action) const;

    bool operator<(const Piece &piece) const {
        return (frequence < piece.frequence || (frequence == piece.frequence && whichPente < piece.whichPente));
    }
    bool operator==(const Piece &piece) const {
        return (frequence == piece.frequence && whichPente == piece.whichPente);
    }
};

#endif // PIECE_H
