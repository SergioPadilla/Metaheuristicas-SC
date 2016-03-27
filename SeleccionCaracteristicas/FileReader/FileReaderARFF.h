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

    Characteristic stringToCharacteristic(string to_parse, int num_attributes);
    vector<Characteristic> readData(int num_attributes);
    pair<vector<string>, int> readHead();
public:
    FileReaderARFF(string pathFile);

    vector<Characteristic> readFile();
};

#endif //SELECCIONCARACTERISTICAS_FILEREADERARFF_H
