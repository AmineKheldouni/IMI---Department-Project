#include "Plane.h"
#include <iostream>
#include <ostream>
#include <conio.h>

using namespace std;


int main(){
    vector<PlanePart> planeParts;
    //for (int i = 0; i < 2; i ++) {
        planeParts.push_back(PlanePart());
    //}
    //vector<Location> path = {Location::PARIS, Location::AMSTERDAM, Location::LONDRES, Location::PARIS, Location::NEWYORK};
    vector<Location> path = {Location::PARIS, Location::LONDRES};
	//Location TRY = { Location::PARIS };
	//int tre = (int)TRY + 1;
	int N = 1000;
	int sum = 0;
	int sum_2 = 0;
	/*for (int i = 0; i < N; i++) {
		Plane plane(path, planeParts, 0, 0);
		sum += plane.heuristique()/N;
		
	}*/
	for (int i = 0; i < N; i++) {
		Plane plane(path, planeParts, 0, 0);
		int aer = plane.heuristique_2();
		//cout << aer << endl;	
		sum_2 += aer / N;
	}
	//cout << "le cout d'heuristique 1 = " << sum << endl;
	cout << "le cout d'heuristique 2 = " << sum_2 << endl;
	Plane plane(path, planeParts, 0, 0);
    map<Plane,pair<vector<bool>,double>> valeurs_actions;
    cout << "la valeur optimale = " <<plane.findValue(valeurs_actions).first << endl;
	_getch();
    
}
