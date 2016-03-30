//
// Created by Sergio Padilla López on 22/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_TRES_NN_H
#define SELECCIONCARACTERISTICAS_TRES_NN_H


#include "../Utils/struct.h"

/**
 * Return the same characteristic with the attributes normalized
 */
vector<Data> normalized(vector<Data> characteristics);
/**
 * Return the interval of definition for each attribute
 */
vector<MaxMin> maxmin(vector<Data> characteristics);
/**
 * Return the distance between two vector
 */
double distance(vector<double> a, vector<double> b);

/**
 * Return the three neighbour
 */
pair<vector<Data>, vector<double>> calculate_Neigbours(Data candidate, vector<Data> characteristics, int pos_candidate);

/**
 * get the majority class of the three neighbours
 */
string get_class(vector<Data> characteristics, vector<double> distances);

/**
 * 3-NN algorithm
 */
bool three_NN(vector<Data> characteristics, int pos_candidate);

#endif //SELECCIONCARACTERISTICAS_TRES_NN_H
