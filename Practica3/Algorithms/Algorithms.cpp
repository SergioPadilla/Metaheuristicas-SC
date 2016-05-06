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

pair <pair<double,vector<int>>, pair<double,vector<int>>> cross(pair<double,vector<int>> chromosome1, pair<double,vector<int>> chromosome2, vector<Data> train){
    int n = chromosome1.second.size() - 1;
    int v1 = Randint(0, n);
    int v2 = Randint(0, n);
    int min, max;
    vector<int> chromosome1_vector = chromosome1.second, chromosome2_vector = chromosome2.second;
    vector<int> song_1, song_2;

    if(v1 < v2){
        min = v1;
        max = v2;
    }
    else{
        min = v2;
        max = v1;
    }

    for (int i = 0; i < n; i++) {
        if (i <= min) {
            song_2.push_back(chromosome1_vector.at(i));
            song_1.push_back(chromosome2_vector.at(i));
        } else if (i > min && i < max) {
            song_1.push_back(chromosome1_vector.at(i));
            song_2.push_back(chromosome2_vector.at(i));
        } else if (i >= max) {
            song_2.push_back(chromosome1_vector.at(i));
            song_1.push_back(chromosome2_vector.at(i));
        }
    }

    return pair <pair<double,vector<int>>, pair<double,vector<int>>>(pair<double,vector<int>>(tasa_clas(song_1, train, train),song_1),
                                                                         pair<double,vector<int>>(tasa_clas(song_2, train, train),song_2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

multimap<double, vector<int>> cross(multimap<double, vector<int>> chromosomes, double probability, vector<Data> train){
    vector<int> order = vector_random(30);
    vector<int> order_cross;
    pair <pair<double,vector<int>>, pair<double,vector<int>>> chromosomes_songs;
    multimap<double, vector<int>> chromosomed_crossed;

    for(int i = 0; i < 30*probability; i++){
        order_cross.push_back(order.at(i));
    }

    for(int i = 0; i < order_cross.size()-1; i+=2) {
        int c1 = order_cross.at(i);
        int c2 = order_cross.at(i + 1);
        multimap<double, vector<int>>::iterator it1 = chromosomes.begin(), it2 = chromosomes.begin();

        for (int j = 0; j < c1; j++)
            it1++;
        for (int j = 0; j < c2; j++)
            it2++;

        chromosomes_songs = cross(*it1, *it2, train);

        chromosomed_crossed.insert(chromosomes_songs.first);
        chromosomed_crossed.insert(chromosomes_songs.second);
    }

    return chromosomed_crossed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair<double, vector<int>> selectBestChromosome(multimap<double,vector<int>> chromosomes){
    vector<int> numbers = vector_random(30);
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
    multimap <double, vector<int>> chromosomes_initials, chromosomes_pre_cross, chromosomes_crossed;
    double pc = 0.7;
    double pm = 0.001;
    int num_gen_to_mute = pm*30*n;
    vector<int> gen_to_mute;
    vector<int> chromosome_to_mute;
    bool elitism_is;

    for(int evaluates = 0; evaluates < 15000;) {

        elitism_is = false;
        gen_to_mute = vector_random(n);
        chromosome_to_mute = vector_random(30);

        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < n; j++)
                chromosome.push_back(Randint(0, 1));

            chromosomes_initials.insert(pair<double, vector<int>>(tasa_clas(chromosome, train, train), chromosome));
            chromosome.clear();
            evaluates++;
        }

        multimap<double, vector<int>>::iterator best = chromosomes_initials.end();
        best--;
        elitism = *best;

        //Selection
        for (int i = 0; i < 30; i++)
            chromosomes_pre_cross.insert(selectBestChromosome(chromosomes_initials));

        //Cross
        chromosomes_crossed = cross(chromosomes_pre_cross, pc, train);
        evaluates+=(30*pc);

        //Mutation
        for (int i = n; i > num_gen_to_mute; i--)
            gen_to_mute.pop_back();

        for (int j = 30; j > num_gen_to_mute; j--)
            chromosome_to_mute.pop_back();

        for (int i = 0; i < num_gen_to_mute; i++) {
            multimap<double, vector<int>>::iterator chromosome_selected = chromosomes_crossed.begin();

            for (int j = 0; j < chromosome_to_mute.at(i); i++)
                chromosome_selected++;

            pair<double, vector<int>> element = *chromosome_selected;
            chromosomes_crossed.erase(element.first);
            element.second.at(gen_to_mute.at(i)) = (element.second.at(gen_to_mute.at(i)) == 1) ? 0 : 1;
            chromosomes_crossed.insert(element);
        }

        //Select elitism
        for (multimap<double, vector<int>>::iterator it = chromosomes_crossed.begin(); it != chromosomes_crossed.end() && !elitism_is; it++) {
            pair<double, vector<int>> element = *it;
            if (element.first == elitism.first && element.second == elitism.second)
                elitism_is == true;
        }

        if (!elitism_is) {
            chromosomes_crossed.erase(chromosomes_crossed.begin());
            chromosomes_crossed.insert(elitism);
        }
    }
}