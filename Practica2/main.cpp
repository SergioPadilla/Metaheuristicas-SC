#include <iostream>
#include <vector>
#include "FileReader/FileReaderARFF.h"
#include "random/random.h"
#include "Algorithms/Algorithms.h"
#include "Algorithms/Functions.h"

using namespace std;

int main() {
    vector<int> solution_sfs;
    vector<int> solution_bl;
    vector<int> solution_es;

    FileReaderARFF reader;
    vector<Data> datas;

    vector<string> classes;
    vector<int> begin_class;
    int count = -1;
    vector<Data> datas_sort;
    vector<Data> train, test;
    int pos;
    clock_t start, end;
    vector<int> ones;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            PRIMERA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(69);
    cerr << endl << "-------------------PARTICION 1------------------" << endl;
    cerr << "////////////// WDBC //////////////" << endl;
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/wdbc2.arff");
    datas = reader.readFile();

    ones = vector<int>(datas.at(0).attributes.size(),1);

    classes = reader.readHead().first;
    count = -1;

    // sort vector by class
    for (string c : classes) {
        for (Data d : datas) {
            if (c == d.clase) {
                datas_sort.push_back(d);
                count++;
            }
        }

        begin_class.push_back(count);
    }

    // Generate two partitions aleatory
    for (int i = 0; i < begin_class.size(); i++) {
        for (int j = begin_class.at(i) - 1; j >= 0; j -= 2) {
            pos = Randint(0, j);
            train.push_back(datas_sort.at(pos));
            datas_sort.erase(datas_sort.begin() + pos);
            pos = Randint(0, j - 1);
            test.push_back(datas_sort.at(pos));
            datas_sort.erase(datas_sort.begin() + pos);
        }

        int value_aux = begin_class.at(i);
        for (int j = 0; j < begin_class.size(); j++) {
            begin_class.at(j) -= value_aux;
        }
    }

    //cerr << "SFSR: " << tasa_clas(BMB(train), train, test) << endl;
    //cerr << "GRASP: " << tasa_clas(GRASP(train), train, test) << endl;
    cerr << "IML: " << tasa_clas(IML(train), train, test) << endl;
}