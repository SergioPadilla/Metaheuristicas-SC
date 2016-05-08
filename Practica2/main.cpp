#include <iostream>
#include <vector>
#include "FileReader/FileReaderARFF.h"
#include "random/random.h"
#include "Algorithms/Algorithms.h"
#include "Algorithms/Functions.h"

using namespace std;

int main() {
    vector<int> solution_bmb;
    vector<int> solution_grasp;
    vector<int> solution_iml;

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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 1
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 1
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            SEGUNDA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(111);
    cerr << endl << "-------------------PARTICION 2------------------" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 2
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 2
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            TERCERA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(24);
    cerr << endl << "-------------------PARTICION 3------------------" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 3
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 3
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            CUARTA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(55);
    cerr << endl << "-------------------PARTICION 4------------------" << endl;
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

    cerr << "----------------train-test----------------" << endl;
    

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 4
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 4
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            QUINTA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(230);
    cerr << endl << "-------------------PARTICION 5------------------" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    
    end = clock()-start;
    

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 5
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 5
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
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

    cerr << "----------------train-test----------------" << endl;

    start = clock();
    //solution_bmb = BMB(train);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, train, test) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(train);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, train, test) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(train);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, train, test) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    //solution_bmb = BMB(test);
    end = clock()-start;
    //cerr << "tiempo BMB: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class BMB: " << tasa_clas(solution_bmb, test, train) << endl;
    //cerr << "tasa_red BMB: " << tasa_red(solution_bmb) << endl;

    start = clock();
    solution_grasp = SFSR(test);
    end = clock()-start;
    cerr << "tiempo GRASP: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class GRASP: " << tasa_clas(solution_grasp, test, train) << endl;
    cerr << "tasa_red GRASP: " << tasa_red(solution_grasp) << endl;

    start = clock();
    //solution_iml = ILS(test);
    end = clock()-start;
    //cerr << "tiempo ILS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    //cerr << "tasa_class de ILS: " << tasa_clas(solution_iml, test, train) << endl;
    //cerr << "tasa_red ILS: " << tasa_red(solution_iml) << endl;

    train.clear();
    test.clear();
    solution_grasp.clear();
    solution_iml.clear();
    solution_bmb.clear();
    begin_class.clear();
    datas.clear();
    ones.clear();
}