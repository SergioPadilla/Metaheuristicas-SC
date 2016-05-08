//
// Created by Sergio Padilla López on 24/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_ALGORITHMS_H
#define SELECCIONCARACTERISTICAS_ALGORITHMS_H

#include "../Utils/struct.h"
#include "../random/random.h"
#include "../K-NN/three_NN.h"
#include <cmath>
#include <map>


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
pair <pair<double,vector<int>>, pair<double,vector<int>>> cross(pair<double,vector<int>> chromosome1, pair<double,vector<int>> chromosome2, vector<Data> train);

/**
 * Auxiliary function to cross a set of chromosomes
 */
multimap<double, vector<int>> cross(multimap<double, vector<int>> chromosomes, double probability, vector<Data> train);

/**
 * Auxiliary function select a chromosome with tournament
 */
pair<double, vector<int>> selectBestChromosome(multimap<double,vector<int>> chromosomes);

/**
 * AGG algorithm
 */
vector<int> AGG(vector<Data> train);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for AGG

/**
 * AGE algorithm
 */
vector<int> AGE(vector<Data> train);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for AGE

#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
