//
// Created by 97252 on 11/01/2023.
//

#ifndef AP1_COMMAND_H
#define AP1_COMMAND_H
#include "defaultIO.h"

class Command{
protected:
    DefaultIO* dio;

public:
    const string description;
    Command(DefaultIO* dio,const string description):dio(dio),description(description){}
    virtual void execute()=0;
    virtual ~Command(){}
};

#endif //AP1_COMMAND_H
