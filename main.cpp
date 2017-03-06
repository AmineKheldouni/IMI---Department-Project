#include "Ligne.h"
#include <iostream>
#include <ostream>
using namespace std;
#include <vector>





tuple<bool,int,int> trouve_ligne(const vector<double> &z, map<Maintenance,double> &y, map<Ligne, double> &couts, const vector<Avion> &avions){
    int num = 0;
    int entier_ligne = 0;
    bool contrainte_satisfaite = true;
    int nombre_lignes = pow(2,T);
    while (contrainte_satisfaite && (num < N && entier_ligne < nombre_lignes)){
        Ligne ligne = Ligne(entier_ligne,avions[num]);
        map<Ligne,double>::iterator it = couts.find(ligne);
        double cl;
        if (it != couts.end()){
            cl = (*it).second ;
        }
        else{
            cl = ligne.calcul_cout();
        }
        double somme_y = 0;
        vector<bool> maintenances;
        decomposition_binaire(entier_ligne, maintenances);
        for (int t = 0; t < T; ++t){
            if (maintenances[t]){
                Maintenance m(t,avions[num].trouve_position(t));
                somme_y = somme_y + y[m];
            }
        }
        contrainte_satisfaite = (cl + somme_y - z[num] >=0);

        if (num == N-1){
            num = 0;
            ++entier_ligne;
        }
        else{
            ++num;
        }
    }
    return (tuple<bool,int,int>(contrainte_satisfaite, num, entier_ligne));
}

int main()
{
    vector<bool> v;
    decomposition_binaire(12,v);
    for (int k=0;k!=v.size();++k){
        cout << v[k] << endl;
    }
    return 0;
}
