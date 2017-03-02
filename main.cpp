#include "Plane.h"
#include <iostream>

using namespace std;


int main(){
    vector<PlanePart> planeParts;
    for (int i = 0; i < 3; i ++) {
        planeParts.push_back(PlanePart());
    }
    Plane plane(Location::HUB, planeParts, 0);
    map<Plane,pair<vector<bool>,double>> valeurs_actions;
    cout << plane.findValue(valeurs_actions).first << endl;

    return 0;
}
