//
// Created by Sergio Padilla López on 24/3/16.
//

#include "Algorithms.h"

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


vector<int> SFS(vector<Characteristic> characteristics){
    vector<Characteristic> F = vector<Characteristic>(characteristics);
    vector<int> S;
    int pos;
    double sol_actual;

    for(int i = 0; i < characteristics.size(); i++){
        S.push_back(0);
    }

    bool fin = false;
    Characteristic promising;

    for(int i = 0; i < 15000 && !F.empty() && !fin; i++){
        promising = ; //Seleccionamos la mas prometedora
        pos = find(F,promising);
        F.erase(F.begin() + pos);
        S.insert(S.begin() + pos, 1);

        // Evaluar S
        // Si mejora a sol_actual;
        //    sol_actual = nueva evaluacion de S
        // Si no
        //    S.insert(S.begin() + pos, 0);
        //    fin = true;
    }

    return S;
}