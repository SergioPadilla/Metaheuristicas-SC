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
 * AM-(10,1.0)
 */
vector<int> AM1(vector<Data> train);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for AM1

/**
 * AM-(10,0.1)
 */
vector<int> AM2(vector<Data> train);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for AM2

/**
 * AM-(10,0.1mej)
 */
vector<int> AM3(vector<Data> train);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for AM3

#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
