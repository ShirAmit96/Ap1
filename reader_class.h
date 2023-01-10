#ifndef AP1_READERCLASS_H
#define AP1_READER_CLASS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "database.h"
using namespace std;

class ReaderClass {
private:
    string fileName;
    bool classifiedFlag;
public:
    ReaderClass();
    bool isClassified(string fileType);
    bool validFile;
    DataBase readCsv(string fileName,  string fileType);

};
#endif //AP1_READERCLASS_H

