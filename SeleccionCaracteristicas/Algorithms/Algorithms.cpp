//
// Created by Sergio Padilla López on 24/3/16.
//

#include "Algorithms.h"

double tasa_clas(vector<int> solution, vector<Characteristic> characteristics){
    double good = 0;

    for(int i = 0; i < solution.size(); i++){
        if(solution.at(i) == 1)
            if(three_NN(characteristics, i))
                good++;
    }

    return 100*good/characteristics.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*vector<int> SFS(vector<Characteristic> characteristics){
    vector<int> F;
    vector<int> S;
    double better_solution = 0; // No characteristics selected
    double new_solution = 0;
    double older_solution = 0;
    int pos_best = -1;
    bool end = false;

    // Init S and F
    for(int i = 0; i < characteristics.size(); i++){
        S.push_back(0);
        F.push_back(1);
    }

    // check if F is empty, count the number of zeros
    int zeros = 0;
    int n = F.size();

    for(int i = 0; i<15000 && zeros != n && !end; i++){ //TODO: a 15000 no llega nunca
        for(int j = 0; j < S.size(); j++){
            if(S.at(j) == 0) {
                S.at(j) = 1;

                new_solution = tasa_clas(S, characteristics); // TODO: la mejora se produce con 1 acierto, luego bastaria con coger el primer acierto
                if (new_solution > better_solution) {
                    better_solution = new_solution;
                    pos_best = j;
                }

                S.at(j) = 0;
            }
        }

        S.at(pos_best) = 1;
        F.at(pos_best) = 0;
        zeros++;

        if(better_solution == older_solution) //if the previous solution is equal to the new solution => nothing better
            end = true;
        else
            older_solution = better_solution;
    }

    return S;
}*/

vector<int> SFS(vector<Characteristic> characteristics){
    int n = characteristics.size();
    vector<int> F = sol_random(n);
    vector<int> S;
    double better_solution = 0; // No characteristics selected
    double new_solution = 0;
    double older_solution = 0;
    int pos_best = -1;
    bool end = false;

    // Init S
    for(int i = 0; i < characteristics.size(); i++){
        S.push_back(0);
    }

    // check if F is empty, count the number of zeros
    int zeros = 0;

    for(int i = 0; i<15000 && zeros != n && !end; i++){
        for(int j = 0; j < F.size(); j++){
            if(F.at(j) == 0) {
                F.at(j) = 1;

                new_solution = tasa_clas(F, characteristics);
                if (new_solution > better_solution) {
                    better_solution = new_solution;
                    pos_best = j;
                }

                F.at(j) = 0;
            }
        }

        S.at(pos_best) = 1;
        F.at(pos_best) = 1;
        zeros++;

        if(better_solution == older_solution) //if the previous solution is equal to the new solution => nothing better
            end = true;
        else
            older_solution = better_solution;
    }

    return S;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> sol_random(int size){
    vector<int> s;

    for(int i = 0; i < size; i++){
        s.push_back(Randint(0,1));
    }

    return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> flip(vector<int> s, int i){
    s.at(i) = (s.at(i) == 0) ? 1 : 0;
    return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
double coolingTemperature(double t_cero, double t_f, double t){
    double beta = (t_cero-t_f)/(M*t_cero*t_f); // ¿M?
    return t / (1+beta*t);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ES(vector<Characteristic> characteristics){
    vector<int> s_cero = sol_random(characteristics.size()); // Get solution initial random
    vector<int> S = vector<int>(s_cero);
    double T_cero = 0.3*C(s_cero)/(-log(0.3)); // C función que calcula el ¿coste? de la solucion
    double T_f = (pow(10,-3) < T_cero) ? pow(10,-3) : 0;
    double T = T_cero;
    int iteration = 15000;

    while(T < T_f || iteration > 0){
        for(int i = 0; i < characteristics.size(); i++){
            vector<int> s_2 = flip(s_cero, Randint(0,s_cero.size()-1));
            double diff = f(s_2)-f(s_cero);

            if(diff < 0){
                s_cero = s_2;

                if(C(s_cero) mejor C(S)){
                    S = s_cero;
                }
            }

        }

        T = coolingTemperature(T_cero, T_f, T);
        iteration--;
    }

    return S;
}*/
