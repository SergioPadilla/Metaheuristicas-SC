//
// Created by Sergio Padilla López on 24/3/16.
//

#include <ostream>
#include <iostream>
#include <map>
#include "Algorithms.h"
#include "Functions.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> SFS(vector<Data> train){
    vector<int> F;
    vector<int> S;
    double new_rate, best_rate;
    best_rate = 0;
    bool end = false;
    int pos_s = -1;
    int pos_f;

    // Init S and F
    for(int i = 0; i < train.at(0).attributes.size(); i++){
        S.push_back(0);
        F.push_back(i);
    }

    for(int i = 0; i < 15000 && !F.empty() && !end; ){
        pos_s = -1;
        for(int j = 0; j < F.size(); j++, i++){
            int value = F.at(j);
            S.at(value) = 1;
            new_rate = tasa_clas(S, train, train);

            if(new_rate > best_rate){
                pos_s = value;
                best_rate = new_rate;
                pos_f = j;
            }

            S.at(value) = 0;
        }

        if(pos_s != -1){
            S.at(pos_s) = 1;
            F.erase(F.begin()+pos_f);
        }
        else
            end = true;
    }

    return S;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> sol_random(int size){
    vector<int> s;

    for(int i = 0; i < size; i++){
        s.push_back(Randint(0,1));
    }

    return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> vector_random(int n){
    vector<int> v;

    for(int i = 0; i < n; i++){
        v.push_back(i);
    }

    random_shuffle(v.begin(), v.end());

    return v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> BL(vector<Data> train, vector<int> solution_initial){
    int n = train.at(0).attributes.size();
    vector<int> S = solution_initial;
    vector<int> S_neighbour = vector<int>(S);
    double new_rate, rate_s;
    bool better = true;

    for(int i = 0; i < 15000 && better; ){
        better = false;
        vector<int> order = vector_random(n);
        for(int j = 0; j < S.size() && !better; j++, i++){
            int pos = order.at(j);
            S_neighbour.at(pos) = (S_neighbour.at(pos) == 1) ? 0 : 1; //flip
            new_rate = tasa_clas(S_neighbour, train, train);

            if(rate_s < new_rate){
                S = S_neighbour;
                rate_s = new_rate;
                better = true;
            }
            else
                S_neighbour.at(pos) = (S_neighbour.at(pos) == 1) ? 0 : 1; // flip back
        }
    }

    return S;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair <pair<double,vector<int>>, pair<double,vector<int>>> cross(pair<double,vector<int>> chromosome1, pair<double,vector<int>> chromosome2, double probability, vector<Data> train){
    if(Randfloat(0,1)>probability)
        return pair <pair<double,vector<int>>, pair<double,vector<int>>>(chromosome1, chromosome2);
    else {
        int n = chromosome1.second.size() - 1;
        int v1 = Randint(0, n); //TODO: comprobar si genera n alguna vez ver en el que tiene que generar 0-1 para ver si genera 1.
        int v2 = Randint(0, n);
        vector<int> chromosome1_vector = chromosome1.second, chromosome2_vector = chromosome2.second;
        vector<int> song_1, song_2;

        for (int i = 0; i < n; i++) {
            if (i <= v1) {
                song_2.push_back(chromosome1_vector.at(i));
                song_1.push_back(chromosome2_vector.at(i));
            } else if (i > v1 && i < v2) {
                song_1.push_back(chromosome1_vector.at(i));
                song_2.push_back(chromosome2_vector.at(i));
            } else if (i >= v2) {
                song_2.push_back(chromosome1_vector.at(i));
                song_1.push_back(chromosome2_vector.at(i));
            }
        }

        return pair <pair<double,vector<int>>, pair<double,vector<int>>>(pair<double,vector<int>>(tasa_clas(song_1, train, train),song_1),
                                                                         pair<double,vector<int>>(tasa_clas(song_2, train, train),song_2));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair<double, vector<int>> selectBestChromosome(multimap<double,vector<int>> chromosomes){
    vector<int> numbers;

    for(int i = 0; i < 30; i++){
        numbers.push_back(i);
    }

    random_shuffle(numbers.begin(), numbers.end());
    int pos_random = Randint(0,28);
    int max = numbers.at(pos_random);

    if(max < numbers.at(pos_random+1))
        max = numbers.at(pos_random+1);

    multimap<double, vector<int>>::iterator it = chromosomes.begin();

    for(int i = 0; i < max; i++)
        it++;

    return pair<double, vector<int>>((*it).first, (*it).second);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> AGG(vector<Data> train){
    int n = train.at(0).attributes.size();
    vector<int> chromosome;
    pair<double, vector<int>> elitism;
    multimap <double, vector<int>> chromosomes_initials, chromosomes_pre_cross, chromosomes_post_cross;
    multimap<double, vector<int>>::iterator chromosome_selected;
    double pc = 0.7;
    double pm = 0.001;

    for(int i = 0; i < 30; i++){
        for(int j = 0; j < n; j++)
            chromosome.push_back(Randint(0,1));

        chromosomes_initials.insert(pair<double, vector<int>>(tasa_clas(chromosome, train, train), chromosome));
        chromosome.clear();
    }

    multimap<double, vector<int>>::iterator best = chromosomes_initials.end();
    best--;
    elitism = *best;

    for(int i = 0; i < 30; i++)
        chromosomes_pre_cross.insert(selectBestChromosome(chromosomes_initials));

    for(multimap<double, vector<int>>::iterator it = chromosomes_pre_cross.begin(); it != chromosomes_pre_cross.end(); ++it) {
        multimap<double, vector<int>>::iterator element = it;
        it++;
        pair <pair<double,vector<int>>, pair<double,vector<int>>> chromosomes_crossed = cross(*element, *it, pc, train);
        chromosomes_post_cross.insert(chromosomes_crossed.first);
        chromosomes_post_cross.insert(chromosomes_crossed.second);
    }
}