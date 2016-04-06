#include <iostream>
#include <map>
#include "FileReader/FileReaderARFF.h"
#include "random/random.h"
#include "Algorithms/Algorithms.h"
#include "Algorithms/Functions.h"
#include <ctime>

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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
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
    solution_sfs = SFS(train);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, train, test) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(train);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, train, test) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(train);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, train, test) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;


    cerr << "----------------test-train-----------------" << endl;

    start = clock();
    solution_sfs = SFS(test);
    end = clock()-start;
    cerr << "Tiempo SFS: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class SFS: " << tasa_clas(solution_sfs, test, train) << endl;
    cerr << "tasa_red SFS: " << tasa_red(solution_sfs) << endl;

    start = clock();
    solution_bl = BL(test);
    end = clock()-start;
    cerr << "Tiempo BL: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class BL: " << tasa_clas(solution_bl, test, train) << endl;
    cerr << "tasa_red BL: " << tasa_red(solution_bl) << endl;

    start = clock();
    solution_es = ES(test);
    end = clock()-start;
    cerr << "Tiempo ES: " << ((double)end)/CLOCKS_PER_SEC << endl;
    cerr << "tasa_class de ES: " << tasa_clas(solution_es, test, train) << endl;
    cerr << "tasa_red ES: " << tasa_red(solution_es) << endl;

    train.clear();
    test.clear();
    solution_bl.clear();
    solution_es.clear();
    solution_sfs.clear();
    begin_class.clear();
    datas.clear();
}