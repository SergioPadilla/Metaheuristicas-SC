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

    for(int i = 0; i < 15000 && !F.empty() && !end; i++){
        pos_s = -1;
        for(int j = 0; j < F.size(); j++){
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
    vector<int> S = sol_random(train.at(0).attributes.size());
    vector<int> S_neighbour = vector<int>(S);
    double new_rate, rate_s;
    bool end = false;
    bool better = true;

    for(int i = 0; i < 15000 && better; i++){
        better = false;
        vector<int> orden = vector_random(S.size());
        for(int j = 0; j < S.size() && !better; j++){
            int pos = orden.at(j);
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

/*
double coolingTemperature(double t_cero, double t_f, double t){
    double beta = (t_cero-t_f)/(15000*t_cero*t_f); // ¿M?
    return t / (1+beta*t);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> ES(vector<Data> characteristics){
    vector<int> s_cero = sol_random(characteristics.size()); // Get solution initial random
    vector<int> S = vector<int>(s_cero);
    double T_cero = 0.3*C(s_cero)/(-log(0.3)); // C función que calcula el ¿coste? de la solucion
    double T_f = (pow(10,-3) < T_cero) ? pow(10,-3) : 0;
    double T = T_cero;
    int iteration = 15000;

    while(T < T_f || iteration > 0){
        for(int i = 0; i < characteristics.size(); i++){
            vector<int> s_2 = flip(s_cero, Randint(0,s_cero.size()-1));
            double diff = f(s_2)-f(s_cero);

            if(diff < 0){
                s_cero = s_2;

                if(C(s_cero) mejor C(S)){
                    S = s_cero;
                }
            }

        }

        T = coolingTemperature(T_cero, T_f, T);
        iteration--;
    }

    return S;
}*/

void anneal (float *x, float *y, int *sol_act, int n_ciudades,
             int n_enfriamientos, float t, float max_vecinos, float max_exitos)

/* Parametros:
      x,y -> Vectores que almacenan las coordenadas de las
         	 ciudades en el plano.
      sol_act -> solucion actual del algoritmo (al principio
            	  contiene la solucion inicial de la que parte).
      n_ciudades -> numero de ciudades del caso del problema.
      t -> Temperatura (al principio contiene el valor de la
           temperatura inicial).
      n_enfriamientos -> Numero maximo de enfriamientos de la temperatura
                     	 a realizar.
      max_vecinos -> Numero maximo de vecinos a generar en cada iteracion
               	   (para cada valor de la temperatura) antes de enfriarla.
      max_exitos -> Numero de exitos a generar en cada iteracion
               	  (para cada valor de la temperatura) antes de enfriarla.
                    Se contabiliza un exito por cada vecino aceptado, ya sea
                    directamente o probabilisticamente por el criterio de
                    Metropolis.

   De este modo, el annealing salta a la siguiente iteracion, es decir, enfria
   la temperatura, cuando se hayan generado max_vecinos O se hayan contabilizado
   max_exitos (lo primero que ocurra) para la temperatura actual.

   En cambio, el algoritmo finaliza su ejecucion cuando se han realizado
   n_enfriamientos iteraciones (es decir, se ha enfriado la temperatura
   n_enfriamientos veces) O cuando para una temperatura no se ha contabilizado
   ningun exito (lo que ocurra antes). */

{
    int i, j, k, n_exitos, aceptar, pos1, pos2, temp;
    int *vecino, *mejor_sol;
    float coste_act, coste_vecino, coste_mejor, de;


    /* Reserva de memoria para las estructuras que almacenan el
       vecino generado para la solucion actual y la mejor solucion
       hallada hasta el momento en la exploracion del espacio */
    vecino = (int *) malloc (n_ciudades*sizeof(int));
    if (vecino==NULL)
    {
        printf("\nERROR DE MEMORIA.\n");
        abort();
    }

    mejor_sol= (int *) malloc (n_ciudades*sizeof(int));
    if (mejor_sol==NULL)
    {
        printf("\nERROR DE MEMORIA.\n");
        abort();
    }

    /* Calculo del coste de la solucion inicial e inicializacion de la
       mejor solucion encontrada hasta el momento a la solucion inicial */
    coste_act=Costo (sol_act,x,y,n_ciudades);
    coste_mejor=coste_act;
    for (i=0;i<n_ciudades;i++)
        mejor_sol[i]=sol_act[i];

    /* Bucle principal del SA */
    for (j=1;j<=n_enfriamientos;j++)
    {
        /* Inicializamos el contador de exitos a 0 para la temperatura actual. */
        n_exitos=0;

        /* Bucle interno: generacion de vecinos para la temperatura actual.
           Finaliza cuando se hayan generado max_vecinos o cuando se hayan
           contabilizado max_exitos. */
        for (k=1;k<=max_vecinos;k++)
        {
            /* Obtencion de un vecino de la solucion actual por inversion */
            Genera_Vecino (sol_act, vecino, n_ciudades, &pos1, &pos2);

            /* Estudiamos si el nuevo vecino es aceptado */
            coste_vecino = Costo (vecino,x,y,n_ciudades);
            de = coste_vecino - coste_act; // TODO: cambiar de orden la resta, cambiar la función de costo
            aceptar = metrop(de,t);

            /* En el caso en que el nuevo vecino es aceptado: */
            if (aceptar)
            {
                /* Contamos un nuevo exito */
                n_exitos++;

                /* Actualizamos la solucion actual */
                coste_act = coste_vecino;
                temp = sol_act[pos1];
                sol_act[pos1] = sol_act[pos2];
                sol_act[pos2] = temp;

                /* Actualizamos la mejor solucion hallada hasta el momento */
                if (coste_act<coste_mejor)
                {
                    coste_mejor = coste_act;
                    for (i=0;i<n_ciudades;i++)
                        mejor_sol[i]=sol_act[i];
                }
            }

            /* Saltamos a la siguiente iteracion (es decir, enfriamos la temperatura)
               si ya hemos sobrepasado el numero de exitos especificado */
            if (n_exitos >= max_exitos) break;
        }

        /* Informe en pantalla */
        printf("\nIteracion: %d.\n",j);
        printf("   T= %10.6f. Numero de exitos: %6d \n",t,n_exitos);
        printf("   Coste Sol. actual = %12.6f. Coste Mejor Sol. = %12.6f \n",coste_act,coste_mejor);

        /* Enfriamiento proporcional de la temperatura */
        t *= TFACTR;

        /* Terminamos la ejecucion del algoritmo en el caso en que no se consiga
           ningun exito para una temperatura concreta */
        if (n_exitos == 0)
            break;
    }

    /* Copiamos la mejor solucion encontrada para devolverla */
    for (i=0;i<n_ciudades;i++)
        sol_act[i]=mejor_sol[i];

    /* Liberamos la memoria empleada */
    free (vecino);
    free (mejor_sol);
    return;
}

#undef TFACTR

