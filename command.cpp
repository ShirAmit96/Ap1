#include "command.h"

string UploadCSV::writeCSV(SharedData* sharedData, string fileContent, bool classified){
    string filePath;
    cout << "line 5" << endl;
    if(!classified){
        cout << fileContent << endl;
    }
    fileContent = fileContent + "END";
    if(!classified){
        cout << fileContent << endl;
    }
    // check if string contain null char, if so delete it.
    if(fileContent.find('\0') !=string::npos ){
        size_t pos = fileContent.find('\0');
        if(!classified){
            cout << pos << endl;
        }
        size_t finalPos = fileContent.find("END");
        if(!classified){
            cout << finalPos << endl;
        }
        fileContent = fileContent.substr(pos+1, finalPos-1);
        if(!classified){
            cout << fileContent << endl;
        }
    }
    if(classified) {
        filePath="classified.csv";
    }else{
        filePath="unClassified.csv";
    }
    std::fstream file;
    file.open(filePath, std::ios::in);
    if(file.good()) {
        std::cout << "File exists, writing to it" << std::endl;
        file.close();
        file.open(filePath, std::ios::out | std::ios::app | std::ios::binary);
        if(file.good()) {
            file.clear();
            file<<fileContent;
            file.close();
        }
    } else {
        std::cout << "File does not exist, creating it" << std::endl;
        file.close();
        file.open(filePath, std::ios::out | std::ios::binary);
        if(file.good()) {
            file.clear();
            file<<fileContent;
            file.close();
        }
    }
    return filePath;
}
void UploadCSV::execute(SharedData *sharedData) {
    dio->write("Please upload your local train CSV file.\n#cmd1*END!");
    string trainFileContent;
    while(true){
        string subFile = dio->read();
        if(subFile.find("*") != string::npos){
            vector<string> spiltString= separateString(subFile,"*");
            trainFileContent+=spiltString[0];
            break;
        }
        trainFileContent+=subFile;

    }
    string trainFile=writeCSV(sharedData,trainFileContent,true);
    ReaderClass read1 = ReaderClass();
    DataBase dbClassified = read1.readCsv(trainFile, "classified");
    cout << "line 33" << endl;
    if (!read1.validFile) {
        dio->write("invalid input.\n");
        return;
        } else {
            dio->write("Upload complete.\n");
            string testFileContent="";
            while(true){
                string subFile = dio->read();
                if(subFile.find("*") != string::npos){
                    vector<string> spiltString= separateString(subFile,"*");
                    testFileContent+=spiltString[0];
                    break;
                }
                trainFileContent+=subFile;
            }
            string testFile=writeCSV(sharedData, trainFileContent, false);
            ReaderClass read2 = ReaderClass();
            DataBase dbUnclassified = read2.readCsv(testFile, "unclassified");
            if (!read2.validFile) {
                dio->write("invalid input.\n");
                return;
            } else {
                dio->write("Upload complete.\n");
                sharedData->db_classified = dbClassified;
                sharedData->db_unclassified = dbUnclassified;
                sharedData->dataUploaded=true;
                // create an instance of Knn
                sharedData->k_model = Knn(sharedData->distanceMetric, sharedData->k, sharedData->db_classified.db);
                // update that Knn instance have been initialized.
                sharedData->k_initialized=true;
                }
            }
        }


void Settings::execute(SharedData *sharedData) {
    string setting = "The current KNN parameters are: K = " + to_string(sharedData->k)+", distance metric = " + sharedData->distanceMetric+"\n*END!";
    dio->write(setting);
    string settingsInput=dio->read();
    // it means that user didn't press only "enter".
    if (settingsInput.length() != 0){
        string delim = " ";
        vector<string> settings = separateString(settingsInput,delim);
        // assign and check if k is valid.
        int k = checkPositiveInt(settings[0]);
        if (k==0){
            dio->write("invalid value for K\n*END!");
            // check if also the metric is not valid.
            if(!checkMetric(settings[1])){
                dio->write("invalid value for metric\n*END!");
            }
            return;
        }
        else{
            // check if distance metric is valid.
            if(!checkMetric(settings[1])){
                dio->write("invalid value for metric\n*END!");
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
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n*END!");
        return;
    }
    else{
        sharedData->k_model.predict(sharedData->db_unclassified);
        sharedData->dataClassified=true;
        dio->write("classifying data complete\n*END!");
    }
}
void DisplayResults::execute(SharedData *sharedData) {
    // check if data is uploaded.
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n*END!");
        // check if also data is not classified - which it will not be because the data have not been uploaded yet.
        if(!sharedData->dataClassified){
            dio->write("please classify the dataa\n*END!");
        }
        return;
    }

    else{
        // check if data was uploaded but not classified.
        if(!sharedData->dataClassified){
            dio->write("please classify the data\n*END!");
            return;
        }
            // in the case data was uploaded and classified.
        else{
            // print the labels after classification.
            for (int i =1 ; i < sharedData->db_unclassified.db.size()+1; i++){
                string classifiedRow = to_string(i) +"\t"+sharedData->db_unclassified.db[i-1].label+"\n*END!";
                dio->write(classifiedRow);
            }
            dio->write("Done.\n*END!");
        }
    }
}
void Download::sendFile(SharedData* sharedData){
    string updateFromClient = dio->read();
        DataBase db=sharedData->db_unclassified;
        string fileContent="";
        for (int i =1 ; i < sharedData->db_unclassified.db.size()+1; i++){
            if(i==sharedData->db_unclassified.db.size()){
                string classifiedRow = to_string(i) +"\t"+sharedData->db_unclassified.db[i-1].label+"\n#EOF*END!";
                dio->write(classifiedRow);
                break;
            }
            string classifiedRow = to_string(i) +"\t"+sharedData->db_unclassified.db[i-1].label+"\n*END!";
            dio->write(classifiedRow);

        }
    }
void Download::execute(SharedData* sharedData) {
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n*END!");
        return;
    }else if(!sharedData->dataClassified){
        dio->write("please classify the data\n*END!");
        return;
    }else {
        dio->write("#cmd5*END!");
        string message = dio->read();
        if(message.find("*pathInserted")!= string::npos) {
            sendFile(sharedData);

        }//else♥♥
        return;
    }
}

void Exit::execute(SharedData* sharedData){}