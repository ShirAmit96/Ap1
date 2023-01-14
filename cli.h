//
// Created by 97252 on 14/01/2023.
//

#ifndef AP1_CLI_H
#define AP1_CLI_H
#include <vector>
#include <algorithm>
#include <string.h>
#include "command.h"
#include "database.h"
using namespace std;

struct SharedData{
    DataBase db_classified;
    DataBase db_unclassified;
    int k = 5;
    string distanceMetric = "AUC";
};

class Cli {
    vector<Command*> commands;
    DefaultIO* dio;
public:
    Cli(DefaultIO* dio);
    void start();
    virtual ~Cli();
};


#endif //AP1_CLI_H
