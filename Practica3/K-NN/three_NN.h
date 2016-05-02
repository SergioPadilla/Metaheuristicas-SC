//
// Created by Sergio Padilla López on 22/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_TRES_NN_H
#define SELECCIONCARACTERISTICAS_TRES_NN_H


#include "../Utils/struct.h"
#include <vector>

class Three_NN {
private:
    vector<Data> clasificator;

public:
    /**
     * Constructor
     */
    Three_NN(vector<Data> train_set){
        clasificator = train_set;
    }

    /**
     * get and set
     */
    void setClasificator(vector<Data> train_set);

    vector<Data> getClasificator();

    /**
     * 3-NN algorithm
     */
    bool evaluate(Data candidate);
};

#endif //SELECCIONCARACTERISTICAS_TRES_NN_H
