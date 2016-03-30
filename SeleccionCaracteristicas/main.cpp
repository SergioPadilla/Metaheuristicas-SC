#include <iostream>
#include <map>
#include "FileReader/FileReaderARFF.h"
#include "random/random.h"
#include "Algorithms/Algorithms.h"

using namespace std;

int main() {
    //start_timers();
    Set_random(69);
    FileReaderARFF reader = FileReaderARFF("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    vector<Data> datas = reader.readFile();

    vector<vector<Data>> v;
    vector<Data> v2;

    // Divide the data in 5 vector for cross validation
    for(int i = 0; i < 5; i++){
        for(int j = i*datas.size()/5; j < (i+1)*datas.size()/5; j++){
            v2.push_back(datas.at(j));
        }
        v.push_back(v2);
        v2.clear();
    }

    vector<pair<vector<Data>, vector<Data>>> partitions;
    vector<string> classes = reader.readHead().first;
    map<string, bool> map_classes;
    vector<Data> t, f;

    for(int j = 0; j < v.size(); j++) {
        for (int i = 0; i < v.at(j).size(); i++) {
            if(map_classes[v.at(j).at(i).clase] == true){
                t.push_back(v.at(j).at(i));
                map_classes[v.at(j).at(i).clase] = false;
            }
            else{
                f.push_back(v.at(j).at(i));
                map_classes[v.at(j).at(i).clase] = true;
            }
        }

        partitions.push_back(pair<vector<Data>, vector<Data>>(t,f));
        t.clear();
        f.clear();
    }

/*    vector<int> solution;
    solution.push_back(1);

    for(int i = 1; i < characteristics.size(); i++){
        solution.push_back(1);
    }*/

    cerr << "stop";
//    cerr << "Porcentaje de acierto: " << tasa_clas(solution, characteristics) << endl;
//    cerr << "Porcentaje de acierto SFS: " << tasa_clas(SFS(characteristics), characteristics);

    //cerr << elapsed_time() << endl;
}