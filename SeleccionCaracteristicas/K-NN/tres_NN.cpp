//
// Created by Sergio Padilla López on 22/3/16.
//

#include <cmath>
#include <iostream>
#include "tres_NN.h"

vector<Characteristic> normalized(vector<Characteristic> characteristics){
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<MaxMin> maxmin(vector<Characteristic> characteristics){
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double distance(vector<double> a, vector<double> b){
    double distance;
    double sum = -1;

    if(a.size() != b.size()){
        cerr << "The vector don't have the same size, impossible to calculate the distance" << endl;
    }
    else {
        for(int i = 0; i < a.size(); i++)
            sum = sum + (a.at(i)-b.at(i))*(a.at(i)-b.at(i));

        return sqrt(sum);
    }

    return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isZero(vector<double> v){
    bool zero = false;

    for(int i = 0; i < v.size(); i++){
        if(v.at(i) == 0)
            zero = true;
    }

    return zero;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TODO: Cambiar vector<double> por characteristic y añadir parametro pos_candidate
vector<Characteristic> calculate_Neigbours(vector<double> candidate, vector<Characteristic> characteristics){
    vector<double> distancies_min;
    vector<Characteristic> neighbours;
    neighbours.reserve(3);
    distancies_min.reserve(3);
    bool zero;
    int pos;

    for(int i = 0; i < 3; i++){
        neighbours.at(i) = characteristics.at(i);
        distancies_min.at(i) = distance(candidate, characteristics.at(i).attributes);
    }

    //if some distance is zero
    zero = isZero(distancies_min);
    if(zero){
        pos = 0;
        if(distancies_min.at(1) == 0){
            pos = 1;
        }
        else if(distancies_min.at(2) == 0){
            pos = 2;
        }

        distancies_min.at(pos) = distance(candidate, characteristics.at(3).attributes);
        neighbours.at(pos) = characteristics.at(3);
        pos = 4; //to use the variable. I need it to the prox for
    }
    else
        pos = 3;

    for(int i = pos; i < characteristics.size(); i++){
        double dist = distance(candidate, characteristics.at(i).attributes);
        if(dist != 0)
            for(int j = 0; j < 3; j++)
                if(dist < distancies_min.at(j)){
                    distancies_min.at(j) = dist;
                    neighbours.at(j) = characteristics.at(i);
                }
    }
//TODO:revisar para coger los que sean iguales
    return neighbours;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string get_class(vector<Characteristic> characteristics, vector<double> distances){
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
                distance_actual == distances.at(i);
                majority_class = characteristics.at(i).clase;
            }
        }
    }

    return majority_class;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool tres_NN(Characteristic candidate, vector<Characteristic> characteristics, int pos_candidate){
    //normalized attributes
    vector<Characteristic> characteristics_normalized = normalized(characteristics);
    Characteristic candidate_normalized = characteristics_normalized.at(pos_candidate);

    // Calculate three neighbours nearest
    vector<Characteristic> neighbours = calculate_Neigbours(candidate_normalized,characteristics_normalized, pos_candidate);

    return get_class(neighbours) == candidate_normalized.clase;
}