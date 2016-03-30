//
// Created by Sergio Padilla López on 24/3/16.
//

#include "Algorithms.h"
#include "Functions.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> SFS(Three_NN clasificator, vector<Data> test){
    vector<int> F;
    vector<int> S;
    double new_rate, best_rate;
    best_rate = 0;
    bool end = false;
    int pos_s = -1;
    int pos_f;

    // Init S and F
    for(int i = 0; i < test.size(); i++){
        S.push_back(0);
        F.push_back(i);
    }

    for(int i = 0; i < 15000 && !F.empty() && !end; i++){
        for(int j = 0; j < F.size(); j++){
            int value = F.at(j);
            S.at(value) = 1;
            new_rate = tasa_clas(S, clasificator.getClasificator(), test);

            if(new_rate > best_rate){
                pos_s = value;
                best_rate = new_rate;
                pos_f = j;
            }

            S.at(j) = 0;
        }

        if(pos_s != -1){
            S.at(pos_s) = 1;
            F.erase(F.begin()+pos_f);
        }
        else
            end = true;
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

vector<int> BL(Three_NN clasificator, vector<Data> test){
    vector<int> S = sol_random(clasificator.getClasificator().size());
    double new_rate, best_rate;
    best_rate = 0;
    bool end = false;
    bool better;

    for(int i = 0; i < 15000 && !end; i++){
        better = false;
        for(int j = 0; j < S.size() && !better; j++){
            S.at(i) = (S.at(i) + 1) % 2; // flip
            new_rate = tasa_clas(S, clasificator.getClasificator(), test);

            if(best_rate < new_rate){
                best_rate = new_rate;
                better = true;
            }
            else
                S.at(i) = (S.at(i) + 1) % 2; // flip back
        }
    }

    return S;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
double coolingTemperature(double t_cero, double t_f, double t){
    double beta = (t_cero-t_f)/(15000*t_cero*t_f); // ¿M?
    return t / (1+beta*t);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ES(vector<Data> characteristics){
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
