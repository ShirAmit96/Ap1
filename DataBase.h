#ifndef AP1_DATABASE_H
#define AP1_DATABASE_H
#include <vector>
#include <string>

using namespace std;

class DataBase {
private:

public:
    struct object{
        string label;
        int size;
        vector<double> values;
    };
    vector<object> db{};

    DataBase(vector<vector<string>> readOutput);
    void createDataBase(vector<vector<string>>readOutput);

};


#endif //AP1_DATABASE_H
