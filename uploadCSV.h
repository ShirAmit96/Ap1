//
// Created by 97252 on 11/01/2023.
//

#ifndef AP1_UPLOADCSV_H
#define AP1_UPLOADCSV_H
#include "command.h"


class UploadCSV:public Command {
    UploadCSV(DefaultIO* dio):Command(dio,"upload an unclassified csv data file\n"){}
    virtual void execute();
};


#endif //AP1_UPLOADCSV_H
