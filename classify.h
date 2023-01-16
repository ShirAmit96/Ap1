//
// Created by leibguy on 17/01/2023.
//

#ifndef AP1_CLASSIFY_H
#define AP1_CLASSIFY_H

#endif //AP1_CLASSIFY_H
#include "command.h"
using namespace std;
class Classify:public Command{
    Classify(DefaultIO* dio):Command(dio,"classify data\n"){}
    virtual void execute(SharedData* sharedData);
};