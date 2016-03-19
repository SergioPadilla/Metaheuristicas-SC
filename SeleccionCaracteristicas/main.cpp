#include <iostream>
#include "Utils/FileReaderARFF.h"

using namespace std;

int main() {
    FileReaderARFF reader = FileReaderARFF("");
    reader.readClass();
    reader.readData();
}