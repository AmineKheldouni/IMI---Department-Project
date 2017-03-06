#ifndef PROJECT_AVION_H
#define PROJECT_AVION_H
#include "Lieu.h"
#include <tuple>
#include <iostream>

using namespace std;

class Maintenance{
    int temps;
    Lieu ville;
public:
    Maintenance(int date, Lieu position){
        temps = date;
        ville = position;
    }
    bool operator<(const Maintenance &m) const{
        return (temps < m.temps || (temps == m.temps && ville < m.ville));
    }
};


class Avion{
    Lieu depart;
    Lieu etranger;
public:
    Lieu trouve_position(int temps) const{
        if (temps%2 == 0){
            return depart;
        }
        else{
            if (depart!=Lieu::PARIS)
                return Lieu::PARIS;
            else
                return etranger;
        }
    }
    Avion(){
        depart = Lieu::PARIS;
        etranger = Lieu::NY;
    }

    Avion(const Avion &a){
        depart = a.depart;
        etranger = a.etranger;
    }
    bool operator<(const Avion &a) const {
        return (depart < a.depart || (depart == a.depart && etranger < a.etranger));
    }
};





#endif
