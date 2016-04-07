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
vector<int> SFS(vector<Data> train);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for SFS

/**
 * Auxiliary function to generate a random solution
 */
vector<int> sol_random(int size);

/**
 *
 */
vector<int> vector_random(int n);

/**
 * Local Search algorithm
 */
vector<int> BL(vector<Data> train);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for BL

/**
 * Auxiliary function to cooling temperature
 */
double coolingTemperature(double t_cero, double t_f, double t, double M);

/**
 * Simulated Annealing algorithm
 */
vector<int> ES(vector<Data> train);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for ES

/**
 * Auxiliary function to check if is tabu-active
 */
bool isTabuActive(int mov, vector<int> tabu_list);

/**
 * Tabú Search algorithm
 */
vector<int> BT(vector<Data> characteristics);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for BT

#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
