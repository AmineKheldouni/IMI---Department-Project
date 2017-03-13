#include "Plane.h"
#include <iostream>
#include <ostream>

using namespace std;


int main(){
    vector<PlanePart> planeParts;
    for (int i = 0; i < 2; i ++) {
        planeParts.push_back(PlanePart());
    }
    //vector<Location> path = {Location::PARIS, Location::AMSTERDAM, Location::LONDRES, Location::PARIS, Location::NEWYORK};
    vector<Location> path = {Location::PARIS, Location::LONDRES};
    Plane plane(path, planeParts, 0, 0);
    map<Plane,pair<vector<bool>,double>> valeurs_actions;
    cout << plane.findValue(valeurs_actions).first << endl;

    return 0;
}
