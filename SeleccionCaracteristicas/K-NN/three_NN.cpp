//
// Created by Sergio Padilla López on 22/3/16.
//

#include <cmath>
#include <iostream>
#include "three_NN.h"

vector<Data> normalized(vector<Data> characteristics){
    vector<Data> normal = vector<Data>(characteristics);
    vector<MaxMin> maxmin_attributes = maxmin(characteristics);

    for(int i = 0; i < characteristics.size(); i++){
        Data characteristic = characteristics.at(i);

        for(int j = 0; j < characteristic.attributes.size(); j++){
            //double attribute_normal = (characteristic.attributes.at(j) - maxmin_attributes.at(j).min) /
              //                                              (maxmin_attributes.at(j).max - maxmin_attributes.at(j).min);
            double num1 = characteristic.attributes.at(j);
            double num2 = maxmin_attributes.at(j).min;
            double num3 = maxmin_attributes.at(j).max;
            double attribute_normal = (num1 - num2) / (num3-num2);
            normal.at(i).attributes.at(j) = (num3-num2)==0 ? 0 : attribute_normal; // don't divide by 0
        }
    }

    return normal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<MaxMin> maxmin(vector<Data> characteristics){
    vector <MaxMin> maxmin_attributes;

    // Initialize with the values of the first
    for(int i = 0; i < characteristics.at(0).attributes.size(); i++){
        maxmin_attributes.push_back(MaxMin(characteristics.at(0).attributes.at(i),characteristics.at(0).attributes.at(i)));
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
    double sum = 0;

    if(a.size() != b.size()){
        cerr << "The vector don't have the same size, impossible to calculate the distance" << endl;
    }
    else {
        for(int i = 0; i < a.size(); i++) {
            double val=a.at(i) - b.at(i);
            sum += (val*val);
        }

        return sqrt(sum);
    }

    return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int max_of_three(vector<double> v){
    int i = 0;

    if(v.at(i) < v.at(1))
        i = 1;
    if(v.at(i) < v.at(2))
        i = 2;

    return i;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair<vector<Data>, vector<double>> calculate_Neigbours(Data candidate, vector<Data> characteristics, int pos_candidate){
    vector<double> distancies_min;
    vector<Data> neighbours_characteristics;
    int pos = 4; // I suppose that pos_candidate are in the first three elements

    for(int i = 0; i < 3; i++){
        neighbours_characteristics.push_back(characteristics.at(i));
        distancies_min.push_back(distance(candidate.attributes, characteristics.at(i).attributes));
    }

    // Leave one out
    if(pos_candidate == 0)
        distancies_min.at(0) = distance(candidate.attributes, characteristics.at(3).attributes);
    else if(pos_candidate == 1)
        distancies_min.at(1) = distance(candidate.attributes, characteristics.at(3).attributes);
    else if(pos_candidate == 2)
        distancies_min.at(2) = distance(candidate.attributes, characteristics.at(3).attributes);
    else
        pos = 3; // if pos_candidate aren't in the first three position

    for(int i = pos; i < characteristics.size(); i++){
        if(i != pos_candidate) {
            double dist = distance(candidate.attributes, characteristics.at(i).attributes);
            int max = max_of_three(distancies_min);

            if (dist < distancies_min.at(max)){
                distancies_min.at(max) = dist;
                neighbours_characteristics.at(max) = characteristics.at(i);
             }
        }
    }

    pair<vector<Data>, vector<double>> neighbours;
    neighbours.first = neighbours_characteristics;
    neighbours.second = distancies_min;

    return neighbours;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string get_class(vector<Data> characteristics, vector<double> distances){
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

bool three_NN(vector<Data> characteristics, int pos_candidate){
    //normalized attributes
    vector<Data> characteristics_normalized = normalized(characteristics);
    Data candidate_normalized = characteristics_normalized.at(pos_candidate);

    // Calculate three neighbours nearest
    pair<vector<Data>, vector<double>> neighbours = calculate_Neigbours(candidate_normalized, characteristics_normalized, pos_candidate);

    return (get_class(neighbours.first, neighbours.second) == candidate_normalized.clase);
}