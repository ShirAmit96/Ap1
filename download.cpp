#include "download.h"
void Download::writeCSV(SharedData* sharedData){
    string resultsPath = dio->read();
    fstream file (resultsPath, ios::out);
    DataBase db=sharedData->db_unclassified;
    int rows =db.db.size();
    if (file.is_open()) {
        for(int i=0; i<rows; i++){
            file<<i+1<<","<<db.db[i].label<<"\n";
        }
        file.close();
    } else {
        dio->write("invalid input\n");
    }
}
void Download::execute(SharedData* sharedData) {
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n");
        return;
    }else if(!sharedData->dataClassified){
        dio->write("please classify the data\n");
        return;
    }else {
        writeCSV(sharedData);
        return;
    }
}