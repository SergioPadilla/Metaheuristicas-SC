//
// Created by Sergio Padilla López on 24/3/16.
//

#include "Algorithms.h"

double tasa_clas(vector<Characteristic> characteristics){
    int good = 0;

    for(int i = 0; i < characteristics.size(); i++){
        if(three_NN(characteristics, i))
            good++;
    }

    return 100*good/characteristics.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double tasa_clas(vector<int> solution, vector<Characteristic> characteristics){
    vector<Characteristic> characteristics_selected;

    for(int i = 0; i < solution.size(); i++){
        if(solution.at(i) == 1){
            characteristics_selected.push_back(characteristics.at(i));
        }
    }

    return tasa_clas(characteristics_selected);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int find(vector<Characteristic> characteristics, Characteristic c){
    bool find = false;
    int pos;

    for(int i = 0; i < characteristics.size() && !find; i++){
        if(characteristics.at(i).equal(c)){
            find = true;
            pos = i;
        }
    }

    return pos;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Characteristic selectPromising(vector<int> solution, vector<Characteristic> characteristics){
    double tax, tax2;
    Characteristic characteristic;

    tax = tasa_clas(solution, characteristics);

    for(int i = 0; i < solution.size(); i++){
        if(solution.at(i) == 0){
            solution.at(i) = 1;
            tax2 = tasa_clas(solution,characteristics);

            if(tax2 > tax){
                tax = tax2;
                characteristic = characteristics.at(i);
            }

            solution.at(i) = 1;
        }
    }

    return characteristic;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> SFS(vector<Characteristic> characteristics){
    vector<Characteristic> F = vector<Characteristic>(characteristics);
    vector<int> S;
    double sol_actual = 0; // No characteristics selected
    double sol_new;

    // Init S
    for(int i = 0; i < characteristics.size(); i++){
        S.push_back(0);
    }

    bool fin = false;
    Characteristic promising;
    int pos;

    for(int i = 0; i < 15000 && !F.empty() && !fin; i++){
        promising = selectPromising(S, characteristics); //Seleccionamos la mas prometedora TODO: ¿Que pasa si ninguna mejora?
        pos = find(F,promising);
        F.erase(F.begin() + pos);
        pos = find(characteristics,promising);
        S.at(pos) = 1;

        // Evaluar S
        sol_new = tasa_clas(S,characteristics);
        // Si mejora a sol_actual;
        if(sol_new > sol_actual) // TODO: esto no tiene sentido, lo he elegido así antes
            sol_actual = sol_new;
        //    sol_actual = nueva evaluacion de S
        // Si no
        //    S.insert(S.begin() + pos, 0);
        //    fin = true;
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
