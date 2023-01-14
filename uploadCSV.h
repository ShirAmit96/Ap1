//
// Created by 97252 on 11/01/2023.
//

#ifndef AP1_UPLOADCSV_H
#define AP1_UPLOADCSV_H
#include "command.h"
#include "reader_class.h"
#include "database.h"
#include "input_validation.h"


class UploadCSV:public Command {
    UploadCSV(DefaultIO* dio):Command(dio,"upload an unclassified csv data file\n"){}
    virtual void execute(SharedData* sharedData);
};


#endif //AP1_UPLOADCSV_H
