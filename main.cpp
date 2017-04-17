#include "Plane.h"
#include <iostream>
#include <ostream>
#include <conio.h>

using namespace std;


int main(){
    vector<PlanePart> planeParts;
    for (int i = 0; i < 2; i ++) {
        planeParts.push_back(PlanePart());
    }
    vector<Location> path = {Location::PARIS, Location::AMSTERDAM, Location::LONDRES, Location::PARIS, Location::NEWYORK};
    //vector<Location> path = {Location::PARIS, Location::LONDRES};
	int N = 1000;
	int sum_2 = 0;
	for (int i = 0; i < N; i++) {
		Plane plane(path, planeParts, 0, 0);
		int aer = plane.heuristique_2();
		sum_2 += aer;
	}
	sum_2 /= N;
	cout << "le cout d'heuristique 2 = " << sum_2 << endl;
	Plane plane(path, planeParts, 0, 0);
    map<Plane,pair<vector<bool>,double>> valeurs_actions;
    cout << "la valeur optimale = " <<plane.findValue(valeurs_actions).first << endl;
	_getch();
    
}
