#include "Etat.h"

Etat::Etat(Location location, const Piece &piece, int temps, double valeur) : location(location), piece(piece),
                                                                              temps(temps), valeur(valeur) {}
