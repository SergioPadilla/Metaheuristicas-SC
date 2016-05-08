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
vector<int> BL(vector<Data> train, vector<int> solution_initial);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for BL

/**
 * Auxiliary function to get the best solutions of a vector of solutions
 */
vector<int> better(vector <int> solutions, vector<Data> train);

/**
 * BMB
 */
vector<int> BMB(vector<Data> train);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for BMB

/**
 * Greedy algorithm random
 * Sequential Forward Selection
 */
vector<int> SFSR(vector<Data> train);

/**
 * GRASP algorithm
 */
vector<int> GRASP(vector<Data> train);

//////////////////////////////////////////////////////////////////////////////////////////////// finish method for GRASP

/**
 * Auxiliary function to mutate n characteristic
 */
vector<int> mutate(vector<int> solution, int n);

/**
 * ILS algorithm
 */
vector<int> ILS(vector<Data> train);

//////////////////////////////////////////////////////////////////////////////////////////////// finish method for GRASP
#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
