#include <iostream>
#include "Utils/FileReaderARFF.h"

using namespace std;

int main() {
    FileReaderARFF reader = FileReaderARFF("/Users/SergioPadilla/GitHub/Metaheuristicas-SC/arrhythmia.arff");
    reader.readFile();
}