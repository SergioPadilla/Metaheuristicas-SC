//
// Created by Sergio Padilla López on 19/3/16.
//

#ifndef SELECCIONCARACTERISTICAS_FILEREADERARFF_H
#define SELECCIONCARACTERISTICAS_FILEREADERARFF_H

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include "struct.h"

using namespace std;


class FileReaderARFF {
private:
    string file;

    Data stringToData(string to_parse);
public:
    FileReaderARFF(string pathFile);

    list<string> readClass();
    list<Data> readData();
};

#endif //SELECCIONCARACTERISTICAS_FILEREADERARFF_H
