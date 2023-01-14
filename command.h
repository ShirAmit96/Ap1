//
// Created by 97252 on 11/01/2023.
//

#ifndef AP1_COMMAND_H
#define AP1_COMMAND_H
#include "defaultIO.h"
#include "database.h"

struct SharedData{
    DataBase db_classified;
    DataBase db_unclassified;
    int k = 5;
    string distanceMetric = "AUC";
    bool dataUploaded=false;
    bool dataClassified=false;
};

class Command{
protected:
    DefaultIO* dio;
public:
    const string description;
    Command(DefaultIO* dio,const string description):dio(dio),description(description){}
    virtual void execute(SharedData* sharedData)=0;
    virtual ~Command(){}
};

#endif //AP1_COMMAND_H
