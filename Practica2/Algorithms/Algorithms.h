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



#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
