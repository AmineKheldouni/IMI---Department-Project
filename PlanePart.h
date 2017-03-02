
#ifndef PlanePart_H
#define PlanePart_H

#include <random>
#include <cstdlib>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class PlanePart
{
    // Il FAUT que pente0 < pente1 < seuil
    const double pente0 = 0.1;
    const double pente1 = 1;
    const double seuil = 3;
    const double probaP0 = 0.9;
    bool whichPente;

public :
    double frequency;
    PlanePart();

    PlanePart(double frequency, bool whichPente);

    void reinitialize();

    bool overBound() const;

    void next(bool action);

    // On retourne la pièce et la probabilité de l'obtenir
    vector<pair<double,PlanePart>> nextPlanePartPossible(bool action) const;

    bool operator<(const PlanePart &PlanePart) const {
        return (frequency < PlanePart.frequency || (frequency == PlanePart.frequency && whichPente < PlanePart.whichPente));
    }
    bool operator==(const PlanePart &PlanePart) const {
        return (frequency == PlanePart.frequency && whichPente == PlanePart.whichPente);
    }
};

#endif // PlanePart_H
