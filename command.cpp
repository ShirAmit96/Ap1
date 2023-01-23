#include "command.h"

string UploadCSV::writeCSV(SharedData* sharedData, string fileContent, bool classified){
    string filePath;
    cout << "line 5" << endl;
    fileContent = fileContent + " ";
    // check if string contain null char, if so delete it.
    size_t pos = fileContent.find('\0');
    size_t finalPos = fileContent.find(" ");
    fileContent = fileContent.substr(pos+1, finalPos-1);
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
        trainFileContent+=subFile;
        if(trainFileContent.find("*END!") != string::npos){
            cout << trainFileContent << endl;
            vector<string> spiltString= separateString(trainFileContent,"*");
            if(spiltString[0].find("failed")!= string::npos){
                return;
            }
            trainFileContent="";
            trainFileContent=spiltString[0];
            break;
        }
    }
    string trainFile=writeCSV(sharedData,trainFileContent,true);
    ReaderClass read1 = ReaderClass();
    DataBase dbClassified = read1.readCsv(trainFile, "classified");
    remove(trainFile.c_str());
    cout << "line 33" << endl;
    if (!read1.validFile) {
        dio->write("invalid input.\n");
        return;
        } else {
            dio->write("Upload complete.\n");
            string testFileContent="";
            while(true){
                string subFileTest ="";
                subFileTest= dio->read();
                testFileContent+=subFileTest;
                cout<<"subfile: "<<subFileTest<<endl;
                if(testFileContent.find("*END!") != string::npos){
                    if(testFileContent.find("failed")!=string::npos){
                        return;
                    }
                    cout<<"test before: "<<testFileContent<<endl;
                    size_t finalPos = testFileContent.find("*");
                    testFileContent = testFileContent.substr(0, finalPos);
                    //vector<string> spiltTestString= separateString(testFileContent,"*");
                    //testFileContent=spiltTestString[0];
                    cout <<"test after: " <<testFileContent<<endl;
                    break;
                }
                cout <<"line 75:"<<testFileContent<<endl;
            }
            string testFile=writeCSV(sharedData, testFileContent, false);
            ReaderClass read2 = ReaderClass();
            DataBase dbUnclassified = read2.readCsv(testFile, "unclassified");
            cout << remove(testFile.c_str()) << endl;
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
    string setting = "The current KNN parameters are: K = " + to_string(sharedData->k)+", distance metric = " + sharedData->distanceMetric+"\n#cmd2*END!";
    dio->write(setting);
    string settingsInput=dio->read();
    // it means that user didn't press only "enter".
    if (settingsInput.length() != 0){
        string delim = " ";
        if(!(settingsInput.find(" ") != string::npos)){
            dio->write("invalid input\n");
        }
        if(&settingsInput[settingsInput.length()-1] != " ") {
            vector<string> settings = separateString(settingsInput, delim);
            // assign and check if k is valid.
            int k = checkPositiveInt(settings[0]);
            if (k == 0) {
                dio->write("invalid value for K\n*END!");
                // check if also the metric is not valid.
                if (!checkMetric(settings[1])) {
                    dio->write("invalid value for metric\n*END!");
                }
            } else {
                cout << k << endl;
                // check if distance metric is valid.
                // the try and catch block is for the cases where the user inserts blank space after the k,
                // and not a Distance Metric alias.
                try {
                    if (!checkMetric(settings[1])) {
                        dio->write("invalid value for metric\n*END!");
                    }
                    else {
                        string distanceMetric = settings[1];
                        cout << distanceMetric << endl;
                        // change metric if it's different from the current setting.
                        if (distanceMetric != sharedData->distanceMetric)
                            sharedData->distanceMetric = distanceMetric;
                        sharedData->k_model.updateDistanceMetric(sharedData->distanceMetric);
                    }
                }
                catch (std::out_of_range& e){
                    dio->write("invalid input\n");
                }
                // change k if it's different from the current setting.
                if (k != sharedData->k) {
                    sharedData->k = k;
                    sharedData->k_model.updateK(sharedData->k);
                }
            }
        }

    }

}
void Classify::execute(SharedData *sharedData) {
    // First check if the data was uploaded.
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n#cmd3*END!");
        return;
    }
    else{
        dio->write("classifying data complete\n#cmd3*END!");
        // classifying the data.
        sharedData->k_model.predict(sharedData->db_unclassified);
        // set the flag to true.
        sharedData->dataClassified=true;
        cout << "classify" << endl;
        return;
    }
}
void DisplayResults::execute(SharedData *sharedData) {
    // check if data is uploaded.
    if(!sharedData->dataUploaded){
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        dio->write("please upload data\n*END!");
        // check if also data is not classified - which it will not be because the data have not been uploaded yet.
        if(!sharedData->dataClassified){
            dio->write("please classify the data\n*END!");
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
            string classifiedRow = "";
            for (int i =1 ; i < sharedData->db_unclassified.db.size()+1; i++) {
                classifiedRow += to_string(i) + "\t" + sharedData->db_unclassified.db[i - 1].label + "\n";
            }
            classifiedRow = classifiedRow + "Done.\n#cmd4*END!";
            dio->write(classifiedRow);
        }
    }
}

void Download::sendFile(SharedData* sharedData){
        string fileContent="";
        // Create variable to store the classified rows inside.
        string classifiedData = "";
        // Loop over the data structure we store the classified labels inside.
        for (int i =1 ; i < sharedData->db_unclassified.db.size()+1; i++){
            // Concat the Data we want to write to the csv file.
                classifiedData += to_string(i) +"\t"+sharedData->db_unclassified.db[i-1].label+"\n";
            }
            // Mark that this is the end of the Data we want to write to the file.
            classifiedData+="#EOF";
            // Send the data to the client through socketIO.
            dio->write(classifiedData);
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