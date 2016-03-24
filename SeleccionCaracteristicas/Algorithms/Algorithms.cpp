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


vector<Characteristic> SFS(vector<Characteristic> characteristics){
    vector<Characteristic> F = vector<Characteristic>(characteristics);
    vector<int> S;

    for(int i = 0; i < characteristics.size(); i++){
        S.push_back(0);
    }

    bool fin = false;
    Characteristic promising;

    for(int i = 0; i < 15000 && !F.empty() && !fin; i++){
        promising = ; //Seleccionamos la mas prometedora
        int pos = find(F,promising);
        F.erase(F.begin() + pos);
    }
}