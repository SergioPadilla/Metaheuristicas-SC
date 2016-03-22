//
// Created by Sergio Padilla López on 22/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_TRES_NN_H
#define SELECCIONCARACTERISTICAS_TRES_NN_H


#include "../Utils/struct.h"

class tres_NN {
private:
    /**
     * Return the same characteristic with the attributes normalized
     */
    vector<Characteristic> normalized(vector<Characteristic> characteristics);
    vector<MaxMin> maxmin(vector<Characteristic> characteristics);
public:
};


#endif //SELECCIONCARACTERISTICAS_TRES_NN_H
