//
// Created by leibguy on 17/01/2023.
//

#ifndef AP1_DISPLAY_RESULTS_H
#define AP1_DISPLAY_RESULTS_H
#include "command.h"
using namespace std;
class DisplayResults:public Command{
    DisplayResults(DefaultIO* dio):Command(dio,"display results\n"){}
    virtual void execute(SharedData* sharedData);
};
#endif //AP1_DISPLAY_RESULTS_H
