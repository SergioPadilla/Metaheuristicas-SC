//
// Created by Sergio Padilla López on 24/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_ALGORITHMS_H
#define SELECCIONCARACTERISTICAS_ALGORITHMS_H

#include "../Utils/struct.h"
#include "../random/random.h"
#include "../K-NN/three_NN.h"
#include <cmath>

/**
 * Greedy algorithm
 * Sequential Forward Selection
 */
vector<int> SFS(vector<Data> train, vector<Data> test);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for SFS

/**
 * Auxiliary function to generate a random solution
 */
vector<int> sol_random(int size);

/**
 * Local Search algorithm
 */
vector<int> BL(vector<Data> train, vector<Data> test);

/**
 * Auxiliary function to cooling temperature
 */
double coolingTemperature(double t_cero, double t_f, double t);

/**
 * Simulated Annealing algorithm
 */
vector<int> ES(vector<Data> characteristics);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for ES

/**
 * Tabú Search algorithm
 */
vector<int> BT(vector<Data> characteristics);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for BT

#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
