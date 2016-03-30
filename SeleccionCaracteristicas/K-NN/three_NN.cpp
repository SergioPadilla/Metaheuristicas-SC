//
// Created by Sergio Padilla López on 22/3/16.
//

#include <cmath>
#include <iostream>
#include "three_NN.h"
#include "../Algorithms/Functions.h"

vector<Data> Three_NN::get_characteristic(vector<int> solution){
    vector<double> aux;
    Data data_modified;
    vector<Data> new_clasificator;
    for(int i = 0; i < clasificator.size(); i++){
        for(int j = 0; solution.size(); j++){
            if(solution.at(j) == 1){
                aux.push_back(clasificator.at(i).attributes.at(j));
            }
        }

        data_modified.attributes = aux;
        data_modified.clase = clasificator.at(i).clase;
        new_clasificator.push_back(data_modified);
        aux.clear();
    }

    return new_clasificator;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string Three_NN::get_class(vector<Data> characteristics, vector<double> distances){
    string majority_class;
    double distance_actual;

    if(characteristics.at(0).clase == characteristics.at(1).clase)
        majority_class = characteristics.at(1).clase;
    else if(characteristics.at(1).clase == characteristics.at(2).clase)
        majority_class = characteristics.at(1).clase;
    else if(characteristics.at(0).clase == characteristics.at(2).clase)
        majority_class = characteristics.at(0).clase;
    else{
        majority_class = characteristics.at(0).clase;
        distance_actual = distances.at(0);

        for(int i = 1; i < 3; i++){
            if(distance_actual > distances.at(i)){
                distance_actual = distances.at(i);
                majority_class = characteristics.at(i).clase;
            }
        }
    }

    return majority_class;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Three_NN::evaluate(vector<Data> characteristics, int pos_candidate){
    //normalized attributes
    vector<Data> characteristics_normalized = normalized(characteristics);
    Data candidate_normalized = characteristics_normalized.at(pos_candidate);

    // Calculate three neighbours nearest
    pair<vector<Data>, vector<double>> neighbours = calculate_Neigbours(candidate_normalized, characteristics_normalized, pos_candidate);

    return (get_class(neighbours.first, neighbours.second) == candidate_normalized.clase);
}