//
// Created by 97252 on 14/01/2023.
//

#include "download.h"

void Download::execute(SharedData* sharedData) {
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n");
        return;
    }
    if(!sharedData->dataClassified){
        dio->write("please classify the data\n");
        return;
    }
    string resultsPath=dio->read();
    thread thread(&DefaultIO::writeCSV,dio, resultsPath, sharedData->db_unclassified);
    thread.detach();
    return;
}