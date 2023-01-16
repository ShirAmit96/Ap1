
#include "classify.h"
void Classify::execute(SharedData *sharedData) {
    if(sharedData->dataUploaded){
        dio->write("please upload data\n");
        return;
    }
    else{
        sharedData->k_model.predict(sharedData->db_unclassified);
        sharedData->dataClassified=true;
        dio->write("classifying data complete\n");
    }
}