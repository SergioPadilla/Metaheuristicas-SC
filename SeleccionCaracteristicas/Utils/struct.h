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
};

struct MaxMin{
    double max;
    double min;
};

#endif //SELECCIONCARACTERISTICAS_STRUCT_H
