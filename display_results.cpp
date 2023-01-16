
#include "display_results.h"
void DisplayResults::execute(SharedData *sharedData) {
    // check if data is uploaded.
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n");
        // check if also data is not classified - which it will not be because the data have not been uploaded yet.
        if(!sharedData->dataClassified){
            dio->write("please classify the data");
        }
        return;
    }
    else{
        // check if data was uploaded but not classified.
        if(!sharedData->dataClassified){
            dio->write("please classify the data");
            return;
        }
        // in the case data was uploaded and classified.
        else{
            // print the labels after classification.
            for (int i =1 ; i < sharedData->db_unclassified.db.size()+1; i++){
                string classifiedRow = to_string(i) +"\t"+sharedData->db_unclassified.db[i].label+"\n";
                dio->write(classifiedRow);
            }
            dio->write("Done.\n");
        }
    }
}