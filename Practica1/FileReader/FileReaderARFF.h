//
// Created by Sergio Padilla López on 19/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_FILEREADERARFF_H
#define SELECCIONCARACTERISTICAS_FILEREADERARFF_H

#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include "struct.h"
#include "../Utils/struct.h"

using namespace std;

class FileReaderARFF {
private:
    string file;

    Data stringToData(string to_parse, int num_attributes);
    vector<Data> readData(int num_attributes);
public:
    FileReaderARFF(string pathFile);
    FileReaderARFF();

    pair<vector<string>, int> readHead();
    vector<Data> readFile();
    void setFile(string pathFile);
};

#endif //SELECCIONCARACTERISTICAS_FILEREADERARFF_H
