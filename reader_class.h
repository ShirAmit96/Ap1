#ifndef AP1_READERCLASS_H
#define AP1_READER_CLASS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "dataBase.h"
using namespace std;

class ReaderClass {
private:
    string fileName;
    string dataType;
    string dataSets;
    string path;
public:
    ReaderClass(string name);
    void setFilesNames(string name);
    void setFilePath();
    DataBase readCsv();

};
#endif //AP1_READERCLASS_H

