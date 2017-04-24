#include "Plane.h"

Plane::Plane(vector<Location> path, const vector<PlanePart> &planeParts, int time, int place) : path(path),
                                                                                 planeParts(planeParts), time(time), place(place) {}



vector<tuple<double, Plane, double>> Plane::nextPlanesPossible(vector<bool> action) const {
    vector<tuple<double, Plane, double>> PlanesWithProba;
    vector<vector<pair<double, PlanePart>>> nextStatesForParts;
	vector<int> multiplierOfPossibleStates;

    for (int i = 0; i < planeParts.size(); i ++) {
        nextStatesForParts.push_back(planeParts[i].nextPlanePartPossible(action[i]));
        multiplierOfPossibleStates.push_back(nextStatesForParts[i].size());
    }

    for (int i = multiplierOfPossibleStates.size() - 2; i >= 0; i --) {
        multiplierOfPossibleStates[i] *= multiplierOfPossibleStates[i + 1];
    }
    multiplierOfPossibleStates.push_back(1);

    vector<pair<double, vector<PlanePart>>> planePartWithProba;
    for (int i = 0; i < multiplierOfPossibleStates[0]; i ++) {
        planePartWithProba.push_back(pair<double, vector<PlanePart>>(1,vector<PlanePart>()));
    }


    for (int i = 0; i < planeParts.size(); i ++) {
        for (int j = 0; j < multiplierOfPossibleStates[0] / multiplierOfPossibleStates[i + 1]; j ++) {
            for (int k = 0; k < multiplierOfPossibleStates[i + 1]; k ++) {
                planePartWithProba[j * multiplierOfPossibleStates[i + 1] + k].first *= nextStatesForParts[i][j%(multiplierOfPossibleStates[i]/multiplierOfPossibleStates[i + 1])].first;
                planePartWithProba[j * multiplierOfPossibleStates[i + 1] + k].second.push_back(nextStatesForParts[i][j%(multiplierOfPossibleStates[i]/multiplierOfPossibleStates[i + 1])].second);
            }
        }
    }

    for (int i = 0; i < planePartWithProba.size(); i ++) {
        int totalCost = 0;
        bool breakDown = false;
        for (int j = 0; j < planePartWithProba[i].second.size(); j ++) {
            // Cas de breakDown sur une pièce
            if (planePartWithProba[i].second[j].overBound()) {
                planePartWithProba[i].second[j].reinitialize();
                totalCost += breakdown;
                breakDown = true;
            }
            else {
                totalCost += (int) path[place % path.size()] * action[j];
            }
        }

        int nextPlace = place;
        // Pas de Panne
        if (!breakDown) {
            nextPlace += 1;
        }

        PlanesWithProba.push_back(tuple<double, Plane, double>(planePartWithProba[i].first,
                                                    Plane(path, planePartWithProba[i].second, time + 1, nextPlace),
                                                               totalCost));
    }

    return PlanesWithProba;
}



// dans le vecteur actions, on retient à l'indice t le choix à faire à la date t permettant d'atteindre le cout minimum renvoyé par la fonction
pair<double, vector<bool>> Plane::findValue(map<Plane,pair<vector<bool>, double>> &valeurs_actions) const {
    if (time == T) {
        // Que mettre en valeur de retour dans ce cas ?
        return pair<double, vector<bool>>(0, vector<bool>());
    }
    else {
        double bestValue;
        vector<bool> action;
        map<Plane, pair<vector<bool>, double>>::iterator it;
        it = valeurs_actions.find(*this);
        if (it != valeurs_actions.end()) {
             bestValue = ((*it).second).second;
             action = ((*it).second).first;
        }
        else {

            action = base10to2(0, planeParts.size());
            vector<tuple<double, Plane, double>> PlanesWithProba = nextPlanesPossible(action);
            bestValue = meanValue(PlanesWithProba, valeurs_actions);

            for (int i = 1; i < pow(2, planeParts.size()); i ++) {
                vector<bool> actionPossible = base10to2(i, planeParts.size());
                PlanesWithProba = nextPlanesPossible(actionPossible);
                double valeur = meanValue(PlanesWithProba, valeurs_actions);

                if (valeur < bestValue) {
                    bestValue = valeur;
                    action = actionPossible;
                }
            }



            valeurs_actions.insert(pair<Plane,pair<vector<bool>, double>>(*this,pair<vector<bool>,double> (action, bestValue)));
        }
        return pair<double, vector<bool>>(bestValue, action);
    }
}


double meanValue(const vector<tuple<double, Plane, double>> &PlanesWithProba, map<Plane,pair<vector<bool>, double>> &valeurs_actions) {
    double valeur = 0;
    for (int i = 0; i < PlanesWithProba.size(); i ++) {
        valeur += get<0>(PlanesWithProba[i]) *
                                     (get<1>(PlanesWithProba[i]).findValue(valeurs_actions).first + get<2>(PlanesWithProba[i]));
    }
    return valeur;
}

// Passe l'entier qui est en base 10 en base 2, en renvoyant un tableau de taille size
vector<bool> base10to2(int integer, int size) {

    vector<bool> vector01;
    while (integer != 0) {
        vector01.push_back((bool) (integer % 2));
        integer = (integer - integer % 2) / 2;
    }

    while (vector01.size() != size) {
        vector01.push_back(false);
    }
    return vector01;
}

//double meanCost(int T, int nb_part, int change){
//    vector<Location> path = {Location::PARIS, Location::LONDRES};
//    vector<PlanePart> planeParts;
//    vector<bool> action0;
//    vector<bool> action1;
//    for(int k=0;k<nb_part;k++){
//        planeParts.push_back(PlanePart());
//        action0.push_back(true);//on change
//        action1.push_back(false);//on change pas
//    }
//    vector<tuple<double, Plane, double>> planePossible;
//    planePossible.push_back(tuple<double, Plane, double>(1,Plane(path, planeParts, 0, 0),0));

//    for(int i=0;i<T;i++){
//        vector<tuple<double, Plane, double>> nextPlanePossible;
//        if(i % change == 0){
//            for(int k=0; k < planePossible.size() ; k++){
//                tuple<double, Plane, double> state = planePossible.back();
//                planePossible.pop_back();
//                vector<tuple<double, Plane, double>> nextStates = get<1>(state).nextPlanesPossible(action0);
//                for(int j =0; j< nextStates.size();j++){
//                    get<0>(nextStates[j]) = get<0>(nextStates[j]) * get<0>(state);
//                    get<2>(nextStates[j]) = get<2>(nextStates[j]) + get<2>(state);
//                    nextPlanePossible.push_back(nextStates[j]);
//                }
//            }
//        }
//        else{
//            for(int k=0; k < planePossible.size() ; k++){
//                tuple<double, Plane, double> state = planePossible.back();
//                planePossible.pop_back();

//                vector<tuple<double, Plane, double>> nextStates = get<1>(state).nextPlanesPossible(action1);
//                for(int j =0; j< nextStates.size();j++){
//                    get<0>(nextStates[j]) = get<0>(nextStates[j]) * get<0>(state);
//                    get<2>(nextStates[j]) = get<2>(nextStates[j])+ get<2>(state);
//                    nextPlanePossible.push_back(nextStates[j]);
//                }
//            }

//        }

//        for(int j =0; j< nextPlanePossible.size();j++){
//            planePossible.push_back(nextPlanePossible[j]);
//        }
//    }
//    double res;
//    for(int i=0;i<planePossible.size();i++){
//        res += get<0>(planePossible[i])* get<2>(planePossible[i]);
//        if (i<50)
//            cout <<get<2>(planePossible[i])<<endl;
//    }
//    return res;
//}

double meanCost(int T, int nb_part, int change){
    vector<Location> path = {Location::PARIS, Location::LONDRES};
    vector<PlanePart> planeParts;
    for(int k=0;k<nb_part;k++){
        planeParts.push_back(PlanePart());
    }
    vector<tuple<double, Plane, double>> planePossible;
    planePossible.push_back(tuple<double, Plane, double>(1,Plane(path, planeParts, 0, 0),0));

    for(int i=0;i<T;i++){
        vector<tuple<double, Plane, double>> nextPlanePossible;
        for(int k=0; k < planePossible.size() ; k++){
            tuple<double, Plane, double> state = planePossible.back();
            planePossible.pop_back();
            vector<bool> action;
            for(int i=0;i < get<1>(state).planeParts.size();i++){

                if(i%change==0){
                    action.push_back(true);

                }
                else{
                    action.push_back(false);

                }

            }
            vector<tuple<double, Plane, double>> nextStates = get<1>(state).nextPlanesPossible(action);
            for(int j =0; j< nextStates.size();j++){
                get<0>(nextStates[j]) = get<0>(nextStates[j]) * get<0>(state);
                get<2>(nextStates[j]) = get<2>(nextStates[j]) + get<2>(state);
                nextPlanePossible.push_back(nextStates[j]);
                }
            }

        for(int j =0; j< nextPlanePossible.size();j++){
            planePossible.push_back(nextPlanePossible[j]);
        }
    }
    double res;
    for(int i=0;i<planePossible.size();i++){
        res += get<0>(planePossible[i])* get<2>(planePossible[i]);
        if (i<50)
            cout <<get<2>(planePossible[i])<<endl;
    }
    return res;
}

double meanCost2(int T, int nb_part, int change){
    vector<Location> path = {Location::PARIS, Location::LONDRES};
    vector<PlanePart> planeParts;
    for(int k=0;k<nb_part;k++){
        planeParts.push_back(PlanePart());
    }
    vector<tuple<double, Plane, double>> planePossible;
    planePossible.push_back(tuple<double, Plane, double>(1,Plane(path, planeParts, 0, 0),0));

    for(int i=0;i<T;i++){
        vector<tuple<double, Plane, double>> nextPlanePossible;
        for(int k=0; k < planePossible.size() ; k++){
            tuple<double, Plane, double> state = planePossible.back();
            planePossible.pop_back();
            vector<bool> action;
            for(int i=0;i < get<1>(state).planeParts.size();i++){

                if(get<1>(state).planeParts[i].temps == change){
                    action.push_back(true);

                }
                else{
                    action.push_back(false);

                }
            }
            vector<tuple<double, Plane, double>> nextStates = get<1>(state).nextPlanesPossible(action);
            for(int j =0; j< nextStates.size();j++){
                get<0>(nextStates[j]) = get<0>(nextStates[j]) * get<0>(state);
                get<2>(nextStates[j]) = get<2>(nextStates[j]) + get<2>(state);
                nextPlanePossible.push_back(nextStates[j]);
                }
            }

        for(int j =0; j< nextPlanePossible.size();j++){
            planePossible.push_back(nextPlanePossible[j]);
        }
    }
    double res;
    for(int i=0;i<planePossible.size();i++){
        res += get<0>(planePossible[i])* get<2>(planePossible[i]);
    }
    return res;
}
