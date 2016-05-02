//
// Created by Sergio Padilla López on 22/3/16.
//

#include <cmath>
#include <iostream>
#include "three_NN.h"
#include "../Algorithms/Functions.h"

bool Three_NN::evaluate(Data candidate){
    // Calculate three neighbours nearest
    pair<vector<Data>, vector<double>> neighbours = calculate_Neigbours(candidate, clasificator);

    return (get_class(neighbours.first, neighbours.second) == candidate.clase);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Three_NN::setClasificator(vector<Data> train_set){
    clasificator = train_set;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Data> Three_NN::getClasificator(){
    return clasificator;
}