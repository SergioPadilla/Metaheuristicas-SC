#include <iostream>
#include "FileReader/FileReaderARFF.h"
#include "random/random.h"
#include "Timer/Timer.h"
#include "Algorithms/Algorithms.h"

using namespace std;

int main() {
    //start_timers();
    Set_random(69);
    FileReaderARFF reader = FileReaderARFF("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    vector<Characteristic> characteristics = reader.readFile();
//    vector<int> solution;
//
//    for(int i = 0; i < characteristics.size(); i++){
//        solution.push_back(Randint(0,1));
//    }
//
    cerr << "Porcentaje de acierto: " << tasa_clas( characteristics);

    //cerr << elapsed_time() << endl;
}