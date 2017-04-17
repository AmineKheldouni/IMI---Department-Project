#include "Plane.h"
#include <iostream>
#include <ostream>

using namespace std;


int main(){
    int T = 100;
    srand(time(NULL));
    vector<PlanePart> planeParts;
    for (int i = 0; i < 1; i ++) {
        planeParts.push_back(PlanePart());
    }
    //vector<Location> path = {Location::PARIS, Location::AMSTERDAM, Location::LONDRES, Location::PARIS, Location::NEWYORK};
    vector<Location> path = {Location::PARIS, Location::LONDRES};
    map<Plane,pair<vector<bool>,double>> valeurs_actions;

    int scenario = 1;

    if (scenario == 0) {

        Plane plane(path, planeParts, 0, 0, T);

        int moyenne = plane.findValue(valeurs_actions).first;

        vector<double> coutTemps;
        for (int i = 0; i < T; i ++){
            pair<double, vector<bool>> coutAction = plane.findValue(valeurs_actions);
            coutTemps.push_back(plane.next(coutAction.second));
        }


        vector<double> cumsum(T);
        std::partial_sum(coutTemps.begin(), coutTemps.end(), cumsum.begin(), plus<double>());

        for (int i = 0; i < cumsum.size(); i ++) {
            cout << cumsum[i] << endl;
        }

        cout << moyenne;
    }
    if (scenario == 1) {


        vector<double> coutTemps;

        for (int i = 0; i <= T; i ++){
            //cerr << i;
            Plane plane(path, planeParts, 0, 0, i);
            cout << plane.findValue(valeurs_actions).first << endl;
        }

    }
    return 0;
}
