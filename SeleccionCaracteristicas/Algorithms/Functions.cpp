//
// Created by Sergio Padilla López on 30/3/16.
//

#include "Functions.h"
#include "../K-NN/three_NN.h"
#include <iostream>
#include <cmath>

vector<Data> normalized(vector<Data> datas){
    vector<Data> normal = vector<Data>(datas);
    vector<MaxMin> maxmin_attributes = maxmin(datas);

    for(int i = 0; i < datas.size(); i++){
        Data data = datas.at(i);

        for(int j = 0; j < data.attributes.size(); j++){
            double num1 = data.attributes.at(j);
            double num2 = maxmin_attributes.at(j).min;
            double num3 = maxmin_attributes.at(j).max;

            normal.at(i).attributes.at(j) = (num3-num2)==0 ? 0 : (num1 - num2) / (num3-num2); // not divide by 0
        }
    }

    return normal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<MaxMin> maxmin(vector<Data> datas){
    vector <MaxMin> maxmin_attributes;

    // Initialize with the values of the first
    for(int i = 0; i < datas.at(0).attributes.size(); i++){
        maxmin_attributes.push_back(MaxMin(datas.at(0).attributes.at(i), datas.at(0).attributes.at(i)));
    }

    for(int i = 1; i < datas.size(); i++){
        for(int j = 0; j < datas.at(i).attributes.size(); j++){
            if(datas.at(i).attributes.at(j) < maxmin_attributes.at(j).min)
                maxmin_attributes.at(j).min = datas.at(i).attributes.at(j);
            else if(datas.at(i).attributes.at(j) > maxmin_attributes.at(j).max)
                maxmin_attributes.at(j).max = datas.at(i).attributes.at(j);
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
    else
        for(int i = 0; i < a.size(); i++) {
            double val=a.at(i) - b.at(i);
            sum += (val*val);
        }

    return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair<vector<Data>, vector<double>> calculate_Neigbours(Data candidate, vector<Data> datas){
    vector<double> distancies_min;
    vector<Data> neighbours_characteristics;
    bool change = true;
    int max;

    for(int i = 0; i < 3; i++){
        neighbours_characteristics.push_back(datas.at(i));
        distancies_min.push_back(distance(candidate.attributes, datas.at(i).attributes));
    }

    for(int i = 3; i < datas.size(); i++){
        double dist = distance(candidate.attributes, datas.at(i).attributes);

        if(change) {
            max = max_of_three(distancies_min);
            change = false;
        }

        if (dist < distancies_min.at(max)){
            distancies_min.at(max) = dist;
            neighbours_characteristics.at(max) = datas.at(i);
            change = true;
        }
    }

    pair<vector<Data>, vector<double>> neighbours;
    neighbours.first = neighbours_characteristics;
    neighbours.second = distancies_min;

    return neighbours;
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

string get_class(vector<Data> datas, vector<double> distances){
    string majority_class;
    double distance_actual;

    if(datas.at(0).clase == datas.at(1).clase)
        majority_class = datas.at(1).clase;
    else if(datas.at(1).clase == datas.at(2).clase)
        majority_class = datas.at(1).clase;
    else if(datas.at(0).clase == datas.at(2).clase)
        majority_class = datas.at(0).clase;
    else{
        majority_class = datas.at(0).clase;
        distance_actual = distances.at(0);

        for(int i = 1; i < 3; i++){
            if(distance_actual > distances.at(i)){
                distance_actual = distances.at(i);
                majority_class = datas.at(i).clase;
            }
        }
    }

    return majority_class;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Data> get_characteristic(vector<int> solution, vector<Data> datas){
    vector<double> aux;
    Data data_modified;
    vector<Data> new_clasificator;
    for(int i = 0; i < datas.size(); i++){
        for(int j = 0; solution.size(); j++)
            if(solution.at(j) == 1)
                aux.push_back(datas.at(i).attributes.at(j));

        data_modified.attributes = aux;
        data_modified.clase = datas.at(i).clase;
        new_clasificator.push_back(data_modified);
        aux.clear();
    }

    return new_clasificator;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double tasa_clas(vector<int> solution, vector<Data> training, vector<Data> test){
    double good = 0;

    vector<Data> training_selected = get_characteristic(solution, training);
    vector<Data> test_selected = get_characteristic(solution, test);

    Three_NN clasificator = Three_NN(training_selected);

    for(int i = 0; i < test_selected.size(); i++){
        if(clasificator.evaluate(test_selected.at(i)))
            good++;
    }

    return 100 * good / test_selected.size();
}