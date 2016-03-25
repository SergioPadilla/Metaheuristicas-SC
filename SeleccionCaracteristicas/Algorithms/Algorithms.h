//
// Created by Sergio Padilla López on 24/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_ALGORITHMS_H
#define SELECCIONCARACTERISTICAS_ALGORITHMS_H

#include "../Utils/struct.h"

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

#endif //SELECCIONCARACTERISTICAS_ALGORITHMS_H
