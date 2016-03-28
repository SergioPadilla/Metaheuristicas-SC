//
// Created by Sergio Padilla López on 19/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_STRUCT_H
#define SELECCIONCARACTERISTICAS_STRUCT_H

#include <list>
#include <string>
#include <vector>

using namespace std;

struct Characteristic {
    vector<double> attributes;
    string clase;

    bool equal(Characteristic c){
        bool is = (attributes == c.attributes && clase == c.clase) ?  true :  false;
        return is;
    }
};

struct MaxMin{
    double max;
    double min;

    MaxMin(double ma, double mi){
        max = ma;
        min = mi;
    }
};

#endif //SELECCIONCARACTERISTICAS_STRUCT_H
