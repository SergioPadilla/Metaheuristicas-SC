//
// Created by Sergio Padilla López on 22/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_TRES_NN_H
#define SELECCIONCARACTERISTICAS_TRES_NN_H


#include "../Utils/struct.h"

/**
 * Return the same characteristic with the attributes normalized
 */
vector<Characteristic> normalized(vector<Characteristic> characteristics);
/**
 * Return the interval of definition for each attribute
 */
vector<MaxMin> maxmin(vector<Characteristic> characteristics);
/**
 * Return the distance between two vector
 */
double distance(vector<double> a, vector<double> b);

/**
 * True if some component is 0
 */
bool isZero(vector<double> v);

/**
 * Return the three neighbour
 */
vector<Characteristic> calculate_Neigbours(vector<double> candidate, vector<Characteristic> characteristics);

/**
 * get the majority class of the three neighbours
 */
string get_class(vector<Characteristic> characteristics);

/**
 * 3-NN algorithm
 */
bool tres_NN(vector<Characteristic> characteristics);

#endif //SELECCIONCARACTERISTICAS_TRES_NN_H
