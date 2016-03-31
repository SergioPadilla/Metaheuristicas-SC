#include <iostream>
#include <map>
#include "FileReader/FileReaderARFF.h"
#include "random/random.h"
#include "Algorithms/Algorithms.h"
#include "Algorithms/Functions.h"

using namespace std;

int main() {
    Set_random(69);
//    FileReaderARFF reader = FileReaderARFF("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff"); //TODO: no estan todas las clases
    FileReaderARFF reader = FileReaderARFF("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    vector<Data> datas = reader.readFile();

    vector<string> classes = reader.readHead().first;
    vector<int> begin_class;
    int count = -1;
    vector<Data> datas_sort;
    vector<Data> train, test;
    int pos;

    // sort vector by class
    for(string c : classes){
        for(Data d : datas){
            if(c == d.clase){
                datas_sort.push_back(d);
                count++;
            }
        }

        begin_class.push_back(count);
    }

    // Generate two partitions aleatory
    for(int i = 0; i < begin_class.size(); i++){
        for(int j = begin_class.at(i)-1; j >= 0 ; j-=2){
            pos = Randint(0,j);
            train.push_back(datas_sort.at(pos));
            begin_class.erase(begin_class.begin()+pos);
            pos = Randint(0,j-1);
            test.push_back(datas_sort.at(pos));
            begin_class.erase(begin_class.begin()+pos);
        }

        for(int j = 0; j < begin_class.size(); j++){
            begin_class.at(j) -= begin_class.at(i);
        }
    }

    cerr << "Porcentaje de acierto SFS: " << tasa_clas(SFS(Three_NN(train), test),train,test);
//    cerr << "Porcentaje de acierto BL: " << tasa_clas(BL(datas), datas);
}