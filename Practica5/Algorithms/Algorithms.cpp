//
// Created by Sergio Padilla López on 24/3/16.
//

#include <ostream>
#include <iostream>
#include <map>
#include "Algorithms.h"
#include "Functions.h"

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

pair<vector<int>,int> BL(vector<Data> train, vector<int> solution_initial){
    int n = train.at(0).attributes.size();
    vector<int> S = solution_initial;
    vector<int> S_neighbour = vector<int>(S);
    double new_rate, rate_s;
    bool better = true;
    int evaluates = 0;

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
        evaluates = i;
    }

    return pair<vector<int>,int>(S,evaluates);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair <pair<double,vector<int>>, pair<double,vector<int>>> cross(pair<double,vector<int>> chromosome1, pair<double,vector<int>> chromosome2, vector<Data> train){
    int n = chromosome1.second.size();
    int v1 = Randint(0, n-1);
    int v2 = Randint(0, n-1);
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
    int n = chromosomes.size();
    vector<int> order = vector_random(n);
    vector<int> order_cross;
    pair <pair<double,vector<int>>, pair<double,vector<int>>> chromosomes_songs;
    multimap<double, vector<int>> chromosomed_crossed;
    int n_cross = n*probability;

    for(int i = 0; i < n_cross; i++){
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

    for(int i = n_cross-1; i < order.size(); i++){
        int v = order.at(i);
        multimap<double, vector<int>>::iterator it = chromosomes.begin();

        for (int j = 0; j < v; j++)
            it++;

        chromosomed_crossed.insert(*it);
    }

    return chromosomed_crossed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair<double, vector<int>> selectBestChromosome(multimap<double,vector<int>> chromosomes){
    int n = chromosomes.size();
    vector<int> numbers = vector_random(n);
    int pos_random = Randint(0,n-2);
    int max = numbers.at(pos_random);

    if(max < numbers.at(pos_random+1))
        max = numbers.at(pos_random+1);

    multimap<double, vector<int>>::iterator it = chromosomes.begin();

    for(int i = 0; i < max; i++)
        it++;

    return pair<double, vector<int>>((*it).first, (*it).second);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair<multimap <double, vector<int>>, int>  BLP(multimap <double, vector<int>> initial, vector<Data> train) {
    multimap<double, vector<int>>::iterator element;
    multimap <double, vector<int>> result;
    int evaluates = 0;

    for(element=initial.begin(); element != initial.end(); ++element) {
        pair<vector<int>, int> evaluation = BL(train, (*element).second);
        evaluates += evaluation.second;
        result.insert(pair<double, vector<int>>(tasa_clas(evaluation.first, train, train), evaluation.first));
        evaluates++;
    }

    return pair<multimap <double, vector<int>>, int>(result, evaluates);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair<multimap <double, vector<int>>, int>  BLP2(multimap <double, vector<int>> initial, vector<Data> train) {
    multimap<double, vector<int>>::iterator element;
    multimap <double, vector<int>> result;
    int evaluates = 0;
    int n = initial.size();
    vector<int> chromosomed_selected;

    for(int i = 0; i < n*0.1; i++) {
        int element = Randint(0,n);
        bool found = false;

        for(int j : chromosomed_selected)
            if(j==element)
                found = true;

        if(!found)
            chromosomed_selected.push_back(element);
        else
            i--;
    }
    sort(chromosomed_selected.begin(), chromosomed_selected.end());

    int i = 0;
    for(element=initial.begin(); element != initial.end(); ++element, i++) {
        bool select = false;

        for(int j = 0; j < chromosomed_selected.size() && !select; j++) {
            if(i == chromosomed_selected.at(j))
                select = true;
        }

        if(select){
            pair<vector<int>, int> evaluation = BL(train, (*element).second);
            evaluates += evaluation.second;
            result.insert(pair<double, vector<int>>(tasa_clas(evaluation.first, train, train), evaluation.first));
            evaluates++;
        }
        else
            result.insert(*element);
    }

    return pair<multimap <double, vector<int>>, int>(result, evaluates);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair<multimap <double, vector<int>>, int>  BLP3(multimap <double, vector<int>> initial, vector<Data> train) {
    multimap<double, vector<int>>::iterator element;
    multimap <double, vector<int>> result;
    int evaluates = 0;
    int n = initial.size();
    int start = (n-n*0.1)-1;


    int i = 0;
    for(element=initial.begin(); element != initial.end(); ++element, i++) {
        if(i > start) {
            pair<vector<int>, int> evaluation = BL(train, (*element).second);
            evaluates += evaluation.second;
            result.insert(pair<double, vector<int>>(tasa_clas(evaluation.first, train, train), evaluation.first));
            evaluates++;
        }
        else
            result.insert(*element);
    }

    return pair<multimap <double, vector<int>>, int>(result, evaluates);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> AM1(vector<Data> train) {
    int n = train.at(0).attributes.size();
    vector<int> chromosome;
    pair<double, vector<int>> elitism;
    multimap <double, vector<int>> chromosomes_initials, chromosomes_pre_cross, chromosomes_crossed, chromosomes_final;
    double pc = 0.7;
    double pm = 0.001;
    int n_chromosomes_initials = 10;
    int num_gen_to_mute = pm*30*n;
    vector<int> gen_to_mute;
    vector<int> chromosome_to_mute;
    bool elitism_is;
    int evaluates = 0;

    for (int i = 0; i < n_chromosomes_initials; i++) {
        for (int j = 0; j < n; j++)
            chromosome.push_back(Randint(0, 1));

        chromosomes_final.insert(pair<double, vector<int>>(tasa_clas(chromosome, train, train), chromosome));
        chromosome.clear();
        evaluates++;
    }

    int generations = 0;
    while(evaluates < 5000) {
        elitism_is = false;
        gen_to_mute = vector_random(n);
        chromosome_to_mute = vector_random(30);

        chromosomes_initials = chromosomes_final;

        multimap<double, vector<int>>::iterator best = chromosomes_initials.end();
        best--;
        elitism = *best;

        //Selection
        chromosomes_pre_cross.clear();
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

            for (int j = 0; j < chromosome_to_mute.at(i); j++)
                chromosome_selected++;

            pair<double, vector<int>> element = *chromosome_selected;
            chromosomes_crossed.erase(chromosome_selected);
            element.second.at(gen_to_mute.at(i)) = (element.second.at(gen_to_mute.at(i)) == 1) ? 0 : 1;
            chromosomes_crossed.insert(pair<double,vector<int>>(tasa_clas(element.second, train, train), element.second));
            evaluates++;
        }

        //Select elitism
        for (multimap<double, vector<int>>::iterator it = chromosomes_crossed.begin(); it != chromosomes_crossed.end() && !elitism_is; it++) {
            pair<double, vector<int>> element = *it;
            if (element.first == elitism.first && element.second == elitism.second)
                elitism_is = true;
        }

        if (!elitism_is) {
            chromosomes_crossed.erase(chromosomes_crossed.begin());
            chromosomes_crossed.insert(elitism);
        }

        generations++;
        if(generations==10){
            generations = 0;
            pair<multimap <double, vector<int>>, int> blp = BLP(chromosomes_crossed, train);
            chromosomes_final = blp.first;
            evaluates += blp.second;
        }
        else
            chromosomes_final = chromosomes_crossed;
    }

    multimap<double, vector<int>>::iterator best_chromosome = chromosomes_final.end();
    best_chromosome--;
    pair<double, vector<int>> solution_final = *best_chromosome;
    return solution_final.second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> AM2(vector<Data> train) {
    int n = train.at(0).attributes.size();
    vector<int> chromosome;
    pair<double, vector<int>> elitism;
    multimap <double, vector<int>> chromosomes_initials, chromosomes_pre_cross, chromosomes_crossed, chromosomes_final;
    double pc = 0.7;
    double pm = 0.001;
    int n_chromosomes_initials = 10;
    int num_gen_to_mute = pm*30*n;
    vector<int> gen_to_mute;
    vector<int> chromosome_to_mute;
    bool elitism_is;
    int evaluates = 0;

    for (int i = 0; i < n_chromosomes_initials; i++) {
        for (int j = 0; j < n; j++)
            chromosome.push_back(Randint(0, 1));

        chromosomes_final.insert(pair<double, vector<int>>(tasa_clas(chromosome, train, train), chromosome));
        chromosome.clear();
        evaluates++;
    }

    int generations = 0;
    while(evaluates < 5000) {
        elitism_is = false;
        gen_to_mute = vector_random(n);
        chromosome_to_mute = vector_random(30);

        chromosomes_initials = chromosomes_final;

        multimap<double, vector<int>>::iterator best = chromosomes_initials.end();
        best--;
        elitism = *best;

        //Selection
        chromosomes_pre_cross.clear();
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

            for (int j = 0; j < chromosome_to_mute.at(i); j++)
                chromosome_selected++;

            pair<double, vector<int>> element = *chromosome_selected;
            chromosomes_crossed.erase(chromosome_selected);
            element.second.at(gen_to_mute.at(i)) = (element.second.at(gen_to_mute.at(i)) == 1) ? 0 : 1;
            chromosomes_crossed.insert(pair<double,vector<int>>(tasa_clas(element.second, train, train), element.second));
            evaluates++;
        }

        //Select elitism
        for (multimap<double, vector<int>>::iterator it = chromosomes_crossed.begin(); it != chromosomes_crossed.end() && !elitism_is; it++) {
            pair<double, vector<int>> element = *it;
            if (element.first == elitism.first && element.second == elitism.second)
                elitism_is = true;
        }

        if (!elitism_is) {
            chromosomes_crossed.erase(chromosomes_crossed.begin());
            chromosomes_crossed.insert(elitism);
        }

        generations++;
        if(generations==10){
            generations = 0;
            pair<multimap <double, vector<int>>, int> blp = BLP2(chromosomes_crossed, train);
            chromosomes_final = blp.first;
            evaluates += blp.second;
        }
        else
            chromosomes_final = chromosomes_crossed;
    }

    multimap<double, vector<int>>::iterator best_chromosome = chromosomes_final.end();
    best_chromosome--;
    pair<double, vector<int>> solution_final = *best_chromosome;
    return solution_final.second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> AM3(vector<Data> train) {
    int n = train.at(0).attributes.size();
    vector<int> chromosome;
    pair<double, vector<int>> elitism;
    multimap <double, vector<int>> chromosomes_initials, chromosomes_pre_cross, chromosomes_crossed, chromosomes_final;
    double pc = 0.7;
    double pm = 0.001;
    int n_chromosomes_initials = 10;
    int num_gen_to_mute = pm*30*n;
    vector<int> gen_to_mute;
    vector<int> chromosome_to_mute;
    bool elitism_is;
    int evaluates = 0;

    for (int i = 0; i < n_chromosomes_initials; i++) {
        for (int j = 0; j < n; j++)
            chromosome.push_back(Randint(0, 1));

        chromosomes_final.insert(pair<double, vector<int>>(tasa_clas(chromosome, train, train), chromosome));
        chromosome.clear();
        evaluates++;
    }

    int generations = 0;
    while(evaluates < 5000) {
        elitism_is = false;
        gen_to_mute = vector_random(n);
        chromosome_to_mute = vector_random(30);

        chromosomes_initials = chromosomes_final;

        multimap<double, vector<int>>::iterator best = chromosomes_initials.end();
        best--;
        elitism = *best;

        //Selection
        chromosomes_pre_cross.clear();
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

            for (int j = 0; j < chromosome_to_mute.at(i); j++)
                chromosome_selected++;

            pair<double, vector<int>> element = *chromosome_selected;
            chromosomes_crossed.erase(chromosome_selected);
            element.second.at(gen_to_mute.at(i)) = (element.second.at(gen_to_mute.at(i)) == 1) ? 0 : 1;
            chromosomes_crossed.insert(pair<double,vector<int>>(tasa_clas(element.second, train, train), element.second));
            evaluates++;
        }

        //Select elitism
        for (multimap<double, vector<int>>::iterator it = chromosomes_crossed.begin(); it != chromosomes_crossed.end() && !elitism_is; it++) {
            pair<double, vector<int>> element = *it;
            if (element.first == elitism.first && element.second == elitism.second)
                elitism_is = true;
        }

        if (!elitism_is) {
            chromosomes_crossed.erase(chromosomes_crossed.begin());
            chromosomes_crossed.insert(elitism);
        }

        generations++;
        if(generations==10){
            generations = 0;
            pair<multimap <double, vector<int>>, int> blp = BLP3(chromosomes_crossed, train);
            chromosomes_final = blp.first;
            evaluates += blp.second;
        }
        else
            chromosomes_final = chromosomes_crossed;
    }

    multimap<double, vector<int>>::iterator best_chromosome = chromosomes_final.end();
    best_chromosome--;
    pair<double, vector<int>> solution_final = *best_chromosome;
    return solution_final.second;
}