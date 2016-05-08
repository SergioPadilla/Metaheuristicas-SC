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

vector<int> better(vector<vector<int>> solutions, vector<Data> train){
    double cost_better = -1;
    double new_cost = -1;
    vector<int> best;

    for(vector<int> v : solutions){
        new_cost = tasa_clas(v, train, train);

        if(new_cost > cost_better){
            cost_better = new_cost;
            best = v;
        }
    }

    return best;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> BMB(vector<Data> train){
    int n = train.at(0).attributes.size();

    vector<vector<int>> solutions;

    for(int i = 0; i < 25; i++)
        solutions.push_back(BL(train, sol_random(n)));

    return better(solutions, train);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> SFSR(vector<Data> train){
    vector<int> F;
    vector<int> S;
    vector<pair<double,int>> LCR;
    multimap<double,int> rates; //Use multimap to sort by key, in this case, key will be tasa_clas of each flip
    double new_rate, best_rate;
    best_rate = 0;
    bool end = false;
    int pos_s = -1;
    int pos_f;
    double alpha = 0.3;

    // Init S and F
    for(int i = 0; i < train.at(0).attributes.size(); i++){
        S.push_back(0);
        F.push_back(i);
    }

    for(int i = 0; i < 15000 && !F.empty() && !end; ){
        pos_s = -1;

        // Evaluate F
        rates.clear();
        for(int k : F) {
            S.at(k) = 1;
            rates.insert(pair<double,int>(tasa_clas(S, train, train),k));
            S.at(k) = 0;
        }

        multimap<double,int>::iterator best_cost = rates.end();
        best_cost--;
        multimap<double,int>::iterator worst_cost = rates.begin();

        double nu = (*best_cost).first - (alpha*((*best_cost).first-(*worst_cost).first));

        multimap<double,int>::iterator pos = rates.insert(pair<double,int>(nu,-1));
        pos++;

        LCR.clear();
        for(pos; pos != rates.end(); ++pos)
            LCR.push_back((*pos));

        random_shuffle(LCR.begin(), LCR.end());

        for(int j = 0; j < LCR.size(); j++, i++){
            pair<double,int> possible = LCR.at(j);
            new_rate = possible.first;

            if(new_rate > best_rate){
                pos_s = possible.second;
                best_rate = new_rate;
                pos_f = j;
            }
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

vector<int> GRASP(vector<Data> train){
    int n = train.at(0).attributes.size();
    vector <vector<int>> solutions;

    for(int sol = 0; sol < 25; sol++) {
        vector<int> S = SFSR(train);
        solutions.push_back(BL(train, S));
    }

    return better(solutions,train);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> mutate(vector<int> solution, int n){
    vector<int> characteristics;

    for(int i = 0; i < solution.size(); i++)
        characteristics.push_back(i);

    random_shuffle(characteristics.begin(), characteristics.end());

    for(int i = 0; i < n; i++){
        int pos = characteristics.at(i);
        solution.at(pos) = (solution.at(pos) == 1) ? 0 : 1;
    }

    return solution;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ILS(vector<Data> train){
    int n = train.at(0).attributes.size();
    int t = 0.1*n;

    vector<int> S = sol_random(n);
    vector<int> best_S = BL(train,S);
    vector<int> mutate_S, possible_S;
    double possible_rate, best_rate = tasa_clas(best_S, train, train);

    for(int i = 0; i < 25; i++){
        mutate_S = mutate(best_S, t);
        possible_S = BL(train, mutate_S);
        possible_rate = tasa_clas(possible_S, train, train);

        if(possible_rate > best_rate){
            best_rate = possible_rate;
            best_S = possible_S;
        }
    }

    return best_S;
}
