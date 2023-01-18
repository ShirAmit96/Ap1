#ifndef AP1_DATABASE_H
#define AP1_DATABASE_H
#include <vector>
#include <string>
#include "input_validation.h"

using namespace std;

class DataBase {
public:
    bool isValid;
    bool isClassified;
    struct object{
        string label;
        int size;
        vector<double> values;
    };
    vector<object> db{};
    void createDataBase(vector<vector<string> > readOutput,bool validFile,bool  classifiedFlag);
};


#endif //AP1_DATABASE_H
