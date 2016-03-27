//
// Created by Sergio Padilla López on 24/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_ALGORITHMS_H
#define SELECCIONCARACTERISTICAS_ALGORITHMS_H

#include "../Utils/struct.h"
#include "../random/random.h"
#include <cmath>

/**
 * Auxiliary function to find a characteristic in a vector
 * Return the position
 */
int find(vector<Characteristic> characteristics, Characteristic c);

/**
 * Greedy algorithm
 * Sequential Forward Selection
 */
vector<int> SFS(vector<Characteristic> characteristics);

////////////////////////////////////////////////////////////////////////////////////////////////// finish method for SFS

/**
 * return a solution random
 */
vector<int> sol_random(int size);

/**
 * cooling scheme
 */
double coolingTemperature(double t_cero, double t_f, double t);

/**
 * Simulated Annealing algorithm
 */
vector<int> flip(vector<int> s, int i);

/**
 * Simulated Annealing algorithm
 */
vector<int> ES(vector<Characteristic> characteristics);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for ES


#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
