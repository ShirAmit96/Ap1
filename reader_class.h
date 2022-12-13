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
public:
    ReaderClass(string name);
    DataBase readCsv();

};
#endif //AP1_READERCLASS_H

