//
// Created by 97252 on 14/01/2023.
//

#ifndef AP1_DOWNLOAD_H
#define AP1_DOWNLOAD_H
#include "command.h"
# include <string>
# include <vector>
#include "database.h"
# include <thread>
# include <fstream>
using namespace std;
class Download:public Command{
    Download(DefaultIO* dio):Command(dio,"download results\n"){}
    virtual void execute(SharedData* sharedData);
    void writeCSV(SharedData* sharedData);
};

#endif //AP1_DOWNLOAD_H
