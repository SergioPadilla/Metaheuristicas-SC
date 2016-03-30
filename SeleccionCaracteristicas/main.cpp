#include <iostream>
#include "FileReader/FileReaderARFF.h"
#include "random/random.h"
#include "Timer/Timer.h"
#include "Algorithms/Algorithms.h"

using namespace std;

int main() {
    //start_timers();
    Set_random(69);
    FileReaderARFF reader = FileReaderARFF("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/movement_libras.arff");
    vector<Characteristic> characteristics = reader.readFile();

    vector<int> solution;
    solution.push_back(1);

    for(int i = 1; i < characteristics.size(); i++){
        solution.push_back(1);
    }

    cerr << "Porcentaje de acierto: " << tasa_clas(solution, characteristics) << endl;
    cerr << "Porcentaje de acierto SFS: " << tasa_clas(SFS(characteristics), characteristics);

    //cerr << elapsed_time() << endl;
}