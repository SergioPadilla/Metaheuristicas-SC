//
// Created by Sergio Padilla López on 22/3/16.
//

#include <cmath>
#include "tres_NN.h"

vector<Characteristic> tres_NN::normalized(vector<Characteristic> characteristics){
    vector<Characteristic> normal = vector<Characteristic>(characteristics);
    vector<MaxMin> maxmin_attributes = maxmin(characteristics);

    for(int i = 0; i < characteristics.size(); i++){
        Characteristic characteristic = characteristics.at(i);

        for(int j = 0; j < characteristic.attributes.size(); j++){
            double attribute_normal = (characteristic.attributes.at(j) - maxmin_attributes.at(j).min) /
                                                            (maxmin_attributes.at(j).max - maxmin_attributes.at(j).min);

            normal.at(i).attributes.at(j) = attribute_normal;
        }
    }

    return normal;
}

vector<MaxMin> tres_NN::maxmin(vector<Characteristic> characteristics){
    vector <MaxMin> maxmin_attributes;

    // Initialize with the values of the first
    for(int i = 0; i < characteristics.at(0).attributes.size(); i++){
        maxmin_attributes.at(i).max = characteristics.at(0).attributes.at(i);
        maxmin_attributes.at(i).min = characteristics.at(0).attributes.at(i);
    }

    for(int i = 1; i < characteristics.size(); i++){
        for(int j = 0; j < characteristics.at(i).attributes.size(); j++){
            if(characteristics.at(i).attributes.at(j) < maxmin_attributes.at(j).min)
                maxmin_attributes.at(j).min = characteristics.at(i).attributes.at(j);
            else if(characteristics.at(i).attributes.at(j) > maxmin_attributes.at(j).max)
                maxmin_attributes.at(j).max = characteristics.at(i).attributes.at(j);
        }
    }

    return maxmin_attributes;
}

