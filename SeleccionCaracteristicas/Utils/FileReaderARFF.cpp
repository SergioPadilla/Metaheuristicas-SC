//
// Created by Sergio Padilla López on 19/3/16.
//

#include "FileReaderARFF.h"

FileReaderARFF::FileReaderARFF(string pathFile){
    file = pathFile;
}

list<string> FileReaderARFF::readClass(){
    list<string> class_readed;
    ifstream f;
    string readed;

    f.open(file);

    if(f.is_open()){
        while(!f.eof()) {
            getline(f, readed);

            bool is = readed.find("@attribute class") != -1;
            if (is) {
                string classes = readed.substr(readed.find("{")+1, readed.find("}"));

                while(classes.find(",") != -1) {
                    int comma_pos = classes.find(",");
                    class_readed.push_back(classes.substr(0, comma_pos));
                    classes.erase(0, comma_pos+2);
                }

                class_readed.push_back(classes.substr(0, classes.size()-1));
            }
        }

        f.close();
    }
    else{
        cout << "Error al abrir el archivo" << endl;
    }

    return class_readed;
}

list<Data> FileReaderARFF::readData(){
    list<Data> data;

    ifstream f;
    string readed;
    bool found = false;

    f.open(file);

    if(f.is_open()){
        while(!f.eof()) {
            getline(f, readed);

            if(found)
                data.push_back(stringToData(readed));
            else
                found = readed.find("@data") != -1;
        }

        f.close();
    }
    else{
        cout << "Error al abrir el archivo" << endl;
    }

    return data;
}

Data FileReaderARFF::stringToData(string to_parse){
    Data data;
    vector<double> attributes;

    for(int i = 0; i < 4; i++){
        string st = to_parse.substr(0,to_parse.find(","));
        attributes.push_back(stod(st));
        to_parse.erase(0, to_parse.find(",")+2);
    }

    data.attributes = attributes;
    data.clase = to_parse;

    return data;
}
