//
// Created by Sergio Padilla López on 24/3/16.
//

#include <ostream>
#include <iostream>
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

vector<int> BL(vector<Data> train){
    int n = train.at(0).attributes.size();
    vector<int> S = sol_random(n);
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


double coolingTemperature(double t_cero, double t_f, double t, double M){
    double beta = (t_cero-t_f)/(M*t_cero*t_f);
    return (t / (1+(beta*t)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ES(vector<Data> train){
    int n = train.at(0).attributes.size();
    vector<int> S_act = sol_random(n);
    vector<int> S = vector<int>(S_act);
    vector<int> S_neighbour = vector<int>(S_act);

    double T_zero = 0.3 * (tasa_clas(S_act, train, train)) / (-log(0.3));
    double T_f = (pow(10,-3) < T_zero) ? pow(10,-3) : 0;
    double T = T_zero;

    int max_neighbour = 5*n;
    int max_success = 0.1*max_neighbour;
    int max_cooling = 15000/max_neighbour;

    int n_success;

    double cost_act = tasa_clas(S_act, train, train);
    double cost_neighbour, cost_better, de;

    bool accept;

    for (int j=1; j <= max_cooling; j++) {
        /* Inicializamos el contador de exitos a 0 para la temperatura actual. */
        n_success=0;

        vector<int> order = vector_random(n);
        /* Bucle interno: generacion de vecinos para la temperatura actual.
           Finaliza cuando se hayan generado max_neighbour o cuando se hayan
           contabilizado max_success. */
        for (int k=1; k <= max_neighbour; k++) {
            /* Obtencion de un vecino de la solucion actual por inversion */
            int pos = order.at(j);
            S_neighbour.at(pos) = (S_neighbour.at(pos) == 1) ? 0 : 1; //flip

            /* Estudiamos si el nuevo vecino es aceptado */
            cost_neighbour = tasa_clas(S_neighbour, train, train);
            de = cost_act - cost_neighbour;
            accept = de < 0.0 || Rand() < exp(-de / T);

            /* En el caso en que el nuevo vecino es aceptado: */
            if (accept) {
                /* Contamos un nuevo exito */
                n_success++;

                /* Actualizamos la solucion actual */
                cost_act = cost_neighbour;
                S_act = S_neighbour;

                /* Actualizamos la mejor solucion hallada hasta el momento */
                if (cost_act > cost_better) {
                    cost_better = cost_act;
                    S = S_act;
                }
            }
            else
                S_neighbour.at(pos) = (S_neighbour.at(pos) == 1) ? 0 : 1; // flip back

            /* Saltamos a la siguiente iteracion (es decir, enfriamos la temperatura)
               si ya hemos sobrepasado el numero de exitos especificado */
            if (n_success >= max_success)
                break;
        }

        /* Enfriamiento de la temperatura */
        T = coolingTemperature(T_zero, T_f, T, j*15000/max_neighbour);

        /* Terminamos la ejecucion del algoritmo en el caso en que no se consiga
           ningun exito para una temperatura concreta */
        if (n_success == 0)
            break;
    }

    return S;
}

#undef TFACTR

