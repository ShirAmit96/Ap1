#ifndef AP1_READERCLASS_H
#define AP1_READERCLASS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "DataBase.h"
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
