
#include <random>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

class PlanePart
{
    // Il FAUT que pente0 < pente1 < seuil
	const double probaP1 = 0.9;
    const double pente0 = 0.1;
    const double pente1 = 1;
    const double seuil = 3;
    bool whichPente;
    double frequency;

public :
    PlanePart();
    int temps;

    PlanePart(double frequency, bool whichPente);
    PlanePart(double frequency, bool whichPente, int temps);
    void reinitialize();

    bool overBound() const;

    void next(bool action);

	bool risque() const;

	bool risquemoins() const;

	bool penteHausse() const;

	bool risqueinter() const;

    // On retourne la pièce et la probabilité de l'obtenir
    vector<pair<double,PlanePart>> nextPlanePartPossible(bool action) const;

    bool operator<(const PlanePart &PlanePart) const {
        return (frequency < PlanePart.frequency || (frequency == PlanePart.frequency && whichPente < PlanePart.whichPente));
    }
    bool operator==(const PlanePart &PlanePart) const {
        return (frequency == PlanePart.frequency && whichPente == PlanePart.whichPente);
    }
};

