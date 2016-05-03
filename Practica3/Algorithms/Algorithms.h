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
 * Auxiliary function to cross two chromosomes
 */
pair <vector<int>, vector<int>> cross(vector <int> chromosome1, vector <int> chromosome2, double probability);

/**
 * Auxiliary function select a chromosome with tournament
 */
pair<double, vector<int>> selectBestChromosome(multimap<double,vector<int>> chromosomes);

/**
 * AGG algorithm
 */
vector<int> AGG(vector<Data> train);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for AGG

#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
