//
// Created by Sergio Padilla López on 24/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_ALGORITHMS_H
#define SELECCIONCARACTERISTICAS_ALGORITHMS_H

#include "../Utils/struct.h"
#include "../random/random.h"
#include <cmath>

/**
 * Function objetive
 * % correct clasifications for the 3-NN
 */
double tasa_clas(vector<Characteristic> characteristic);

/**
 * Auxiliary function to find a characteristic in a vector of characteristics
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
 * Auxiliary function to generate a random solution
 */
vector<int> sol_random(int size);

/**
 * Auxiliary function to cooling temperature
 */
double coolingTemperature(double t_cero, double t_f, double t);

/**
 * Auxiliary function to generate new neighbour solution
 */
vector<int> flip(vector<int> s, int i);

/**
 * Simulated Annealing algorithm
 */
vector<int> ES(vector<Characteristic> characteristics);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for ES

/**
 * Tabú Search algorithm
 */
vector<int> BT(vector<Characteristic> characteristics);

/////////////////////////////////////////////////////////////////////////////////////////////////// finish method for BT

#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
