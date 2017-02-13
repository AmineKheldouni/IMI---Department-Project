
#ifndef PIECE_H
#define PIECE_H

#include <random>
#include <cstdlib>

class Piece
{
    const static double pente0 = 0.1;
    const static double pente1 = 1;
    const static double seuil = 3;
    const static double probaP0 = 0.9;
    double frequence;
    bool whichPente;
public :
    Piece();
    void Next(bool action);
};

#endif // PIECE_H
