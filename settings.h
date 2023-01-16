//
// Created by leibguy on 16/01/2023.
//

#ifndef AP1_SETTINGS_H
#define AP1_SETTINGS_H

#include "command.h"
using namespace std;
class Settings:public Command{
    Settings(DefaultIO* dio):Command(dio,"algorithm settings\n"){}
    virtual void execute(SharedData* sharedData);
};

#endif //AP1_SETTINGS_H