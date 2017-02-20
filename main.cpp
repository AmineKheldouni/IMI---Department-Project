#include "Plane.h"
#include <iostream>

using namespace std;


int main(){
    Plane plane(Location::HUB, PlanePart(), 0);
    map<Plane,pair<bool,double>> valeurs_actions;
    cout << plane.findValue(valeurs_actions).first << endl;

    return 0;
}
