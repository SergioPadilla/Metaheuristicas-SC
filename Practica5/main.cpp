#include <iostream>
#include <vector>
#include "FileReader/FileReaderARFF.h"
#include "random/random.h"
#include "Algorithms/Algorithms.h"
#include "Algorithms/Functions.h"

using namespace std;

int main() {
    vector<int> solution_am1;
    vector<int> solution_am2;
    vector<int> solution_am3;

    FileReaderARFF reader;
    vector<Data> datas;

    vector<string> classes;
    vector<int> begin_class;
    int count = -1;
    vector<Data> datas_sort;
    vector<Data> train, test;
    int pos;
    clock_t start, end;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            PRIMERA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(69);
    cerr << endl << "-------------------PARTICION 1------------------" << endl;
    cerr << "////////////// WDBC //////////////" << endl;
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/wdbc2.arff");
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 1
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 1
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            SEGUNDA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(111);
    cerr << endl << "-------------------PARTICION 2------------------" << endl;
    cerr << "////////////// WDBC //////////////" << endl;
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/wdbc2.arff");
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 2
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 2
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
    datas = reader.readFile();

    

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            TERCERA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(24);
    cerr << endl << "-------------------PARTICION 3------------------" << endl;
    cerr << "////////////// WDBC //////////////" << endl;
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/wdbc2.arff");
    datas = reader.readFile();

    

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 3
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
    datas = reader.readFile();

    

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;


    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 3
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
    datas = reader.readFile();

    

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            CUARTA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(55);
    cerr << endl << "-------------------PARTICION 4------------------" << endl;
    cerr << "////////////// WDBC //////////////" << endl;
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/wdbc2.arff");
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 4
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 4
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////                            QUINTA EJECUCION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Set_random(230);
    cerr << endl << "-------------------PARTICION 5------------------" << endl;
    cerr << "////////////// WDBC //////////////" << endl;
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/wdbc2.arff");
    datas = reader.readFile();

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////// wdbc 5
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    cerr << "////////////// LIBRAS //////////////" << endl;
    datas = reader.readFile();

    

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// libras 5
    reader.setFile("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    cerr << "////////////// ARRYTMIA //////////////" << endl;
    datas = reader.readFile();

    

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
    solution_am1 = AM1(train);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, train, test) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(train);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, train, test) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(train);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, train, test) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_am1 = AM1(test);
    end = clock()-start;
    cerr << "Tiempo AM1: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM1: " << tasa_clas(solution_am1, test, train) << endl;
    cerr << "tasa_red AM1: " << tasa_red(solution_am1) << endl;

    start = clock();
    solution_am2 = AM2(test);
    end = clock()-start;
    cerr << "Tiempo AM2: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM2: " << tasa_clas(solution_am2, test, train) << endl;
    cerr << "tasa_red AM2: " << tasa_red(solution_am2) << endl;

    start = clock();
    solution_am3 = AM3(test);
    end = clock()-start;
    cerr << "Tiempo AM3: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class AM3: " << tasa_clas(solution_am3, test, train) << endl;
    cerr << "tasa_red AM3: " << tasa_red(solution_am3) << endl;

    train.clear();
    test.clear();
    solution_am2.clear();
    solution_am3.clear();
    solution_am1.clear();
    begin_class.clear();
    datas.clear();
}