#include "command.h"

void UploadCSV::execute(SharedData *sharedData) {
    dio->write("Please upload your local train CSV file.\n");
    string trainFile = dio->read();
    if (!validFile(trainFile)) {
        dio->write("invalid input.\n");
        return;
    } else {
        ReaderClass read1 = ReaderClass();
        DataBase dbClassified = read1.readCsv(trainFile, "classified");
        if (!read1.validFile) {
            dio->write("invalid input.\n");
            return;
        } else {
            dio->write("Upload complete.");
            dio->write("Please upload your local test CSV file.\n");
            string testFile = dio->read();
            if (!validFile(testFile)) {
                dio->write("invalid input.\n");
                return;
            } else {
                ReaderClass read2 = ReaderClass();
                DataBase dbUnclassified = read2.readCsv(testFile, "unclassified");
                if (!read2.validFile) {
                    dio->write("invalid input.\n");
                    return;
                } else {
                    dio->write("Upload complete.");
                    sharedData->db_classified = dbClassified;
                    sharedData->db_unclassified = dbUnclassified;
                    sharedData->dataUploaded=true;
                    // create an instance ok Knn
                    sharedData->k_model = Knn(sharedData->distanceMetric, sharedData->k, sharedData->db_classified.db);
                    // update that Knn instance have been initialized.
                    sharedData->k_initialized=true;
                }
            }
        }
    }
}

void Settings::execute(SharedData *sharedData) {
    string setting = "The current KNN parameters are: K = " + to_string(sharedData->k)+", distance metric = " + sharedData->distanceMetric+"\n";
    dio->write(setting);
    string settingsInput=dio->read();
    // it means that user didn't press only "enter".
    if (settingsInput.length() != 0){
        string delim = " ";
        vector<string> settings = separateString(settingsInput,delim);
        // assign and check if k is valid.
        int k = checkPositiveInt(settings[0]);
        if (k==0){
            dio->write("invalid value for K\n");
            // check if also the metric is not valid.
            if(!checkMetric(settings[1])){
                dio->write("invalid value for metric\n");
            }
            return;
        }
        else{
            // check if distance metric is valid.
            if(!checkMetric(settings[1])){
                dio->write("invalid value for metric\n");
                return;
            }
            else{
                string distanceMetric = settings[1];
                // change metric if it's different from the current setting.
                if (distanceMetric != sharedData->distanceMetric)
                    sharedData->distanceMetric = distanceMetric;
                sharedData->k_model.updateDistanceMetric(sharedData->distanceMetric);
            }
            // change k if it's different from the current setting.
            if(k!=sharedData->k){
                sharedData->k = k;
                sharedData->k_model.updateK(sharedData->k);
            }
        }

    }

}
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

void Exit::execute(SharedData* sharedData){}