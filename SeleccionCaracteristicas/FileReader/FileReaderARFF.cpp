//
// Created by Sergio Padilla López on 19/3/16.
//

#include "FileReaderARFF.h"
#include "../Algorithms/Functions.h"

FileReaderARFF::FileReaderARFF(string pathFile){
    file = pathFile;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pair <vector<string>, int> FileReaderARFF::readHead(){
    vector<string> class_readed;
    ifstream f;
    string readed;
    int num_attributes = 0;

    f.open(file);

    if(f.is_open()){
        while(!f.eof()) {
            getline(f, readed);

            bool is = readed.find("@attribute Class") != -1 || readed.find("@attribute class") != -1;
            if (is) {
                string classes = readed.substr(readed.find("{")+1, readed.find("}"));

                while(classes.find(",") != -1) {
                    int comma_pos = classes.find(",");
                    class_readed.push_back(classes.substr(0, comma_pos));
                    classes.erase(0, comma_pos+1);
                }

                class_readed.push_back(classes.substr(0, classes.find("}")));
            }
            else if(readed.find("@attribute") != -1){
                num_attributes++;
            }
        }

        f.close();
    }
    else{
        cout << "Error al abrir el archivo" << endl;
    }

    pair <vector<string>, int> pair;
    pair.first = class_readed;
    pair.second = num_attributes;

    return pair;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Data> FileReaderARFF::readData(int num_attributes){
    vector<Data> data;

    ifstream f;
    string readed;
    bool found = false;

    f.open(file);

    if(f.is_open()){
        while(!f.eof()) {
            getline(f, readed);

            if(found && readed != "")
                data.push_back(stringToData(readed, num_attributes));
            else
                found = readed.find("@data") != -1;
        }

        f.close();
    }
    else{
        cout << "Error al abrir el archivo" << endl;
    }

    return normalized(data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Data FileReaderARFF::stringToData(string to_parse, int num_attributes){
    Data data;
    vector<double> attributes;

    for(int i = 0; i < num_attributes; i++){
        string st = to_parse.substr(0,to_parse.find(","));
        attributes.push_back(stod(st));
        to_parse.erase(0, to_parse.find(",")+1);
    }

    data.attributes = attributes;

    if(to_parse[to_parse.size()-1] == '\r'){
        to_parse.erase(to_parse.size()-1);
    }

    data.clase = to_parse;

    return data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Data> FileReaderARFF::readFile(){
    pair <vector<string>,int> pair1 = readHead();
    return readData(pair1.second);
}
