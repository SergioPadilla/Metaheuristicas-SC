//
// Created by Sergio Padilla López on 30/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_FUNCTIONS_H
#define SELECCIONCARACTERISTICAS_FUNCTIONS_H

#include "../Utils/struct.h"

/**
 * Return the pos of the maximun value in the vector
 */
int max_of_three(vector<double> v);

/**
 * Return the same characteristic with the attributes normalized
 */
vector<Data> normalized(vector<Data> datas);

/**
 * Return the interval of definition for each attribute
 */
vector<MaxMin> maxmin(vector<Data> datas);

/**
 * Return the distance between two vector
 */
double distance(vector<double> a, vector<double> b);

/**
 * Return the three neighbour
 */
pair<vector<Data>, vector<double>> calculate_Neigbours(Data candidate, vector<Data> datas);

/**
 * get the majority class of the three neighbours
 */
string get_class(vector<Data> datas, vector<double> distances);

/**
 * Auxiliary function to select Characteristic of the clasificator depend on the solution
 */
vector<Data> get_characteristic(vector<int> solution, vector<Data> datas);

/**
 * Function objetive
 * % correct clasifications for the 3-NN
 */
double tasa_clas(vector<int> solution, vector<Data> training, vector<Data> test);

#endif //SELECCIONCARACTERISTICAS_FUNCTIONS_H
