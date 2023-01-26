#include "command.h"
/*This function gets sharedData struct, a file content string and classified flag and
  writes the string into a temp csv file and which is name is "<socket number><classified/unclassified>"*/
string UploadCSV::writeCSV(SharedData* sharedData, string fileContent, bool classified){
    string filePath;
    //determine the name of the file according to socket and by its type:
    filePath=to_string(sharedData->socket);
    if(classified) {
        filePath+="classified.csv";
    }else{
        filePath+="unClassified.csv";
    }
    std::fstream file;
    // check if the file exists:
    file.open(filePath, std::ios::in);
    // if the file is exists:
    if(file.good()) {
        //clear the file:
        file.open(filePath, std::ios::out | std::ios::app | std::ios::binary);
        if(file.good()) {
            file.clear();
            //write the content into the file:
            file<<fileContent;
            file.close();
        }
    } else {
        // if file doesn't exist,create a new one and write to it:
        file.open(filePath, std::ios::out | std::ios::binary);
        if(file.good()) {
            file.clear();
            file<<fileContent;
            file.close();
        }
    }
    return filePath;
}
/*This function executes command #1.It gets a classified file content, check if it valid and saves it in db.
 * then, it performs the same process with an un classified file.*/
void UploadCSV::execute(SharedData *sharedData) {
    // send the command to the client using dio:
    dio->write("Please upload your local train CSV file.\n#cmd1@@");
    // get train file content from the client:
    string trainFileContent= dio->read();
    // check if reading the file failed in client:
    if (trainFileContent.find("failed") != string::npos) {
        return;
    }
    // write the train file content into a temp file:
    string trainFile = writeCSV(sharedData, trainFileContent, true);
    // create a db that will hold the train file content:
    ReaderClass read1 = ReaderClass();
    DataBase dbClassified = read1.readCsv(trainFile, "classified");
    // remove the temp file created:
    remove(trainFile.c_str());
    // if the file is not valid send a message to the client and return:
    if (!read1.validFile) {
        dio->write("invalid input.\n@@");
        return;
    } else {
        // tell the client upload of first file is complete:
        dio->write("Upload complete.\n@@");
        // get test file content from the client:
        string testFileContent = "";
        testFileContent = dio->read();
        // check if the uploading in client has failed:
        if (testFileContent.find("failed") != string::npos) {
                return;
        }
        // write the train file content into a temp file:
        string testFile = writeCSV(sharedData, testFileContent, false);
        // create a db that will hold the train file content:
        ReaderClass read2 = ReaderClass();
        DataBase dbUnclassified = read2.readCsv(testFile, "unclassified");
        // remove  the temp file created:
        remove(testFile.c_str());
        //if the file is not valid or doesn't match the num of columns in the classified file-return:
        if (!read2.validFile || dbUnclassified.db[0].size + 1 != dbClassified.db[0].size) {
            dio->write("invalid input.\n@@");
            return;
        } else {
            dio->write("Upload complete.\n@@");
            // save the new db's in the sharedData struct:
            sharedData->db_classified = dbClassified;
            sharedData->db_unclassified = dbUnclassified;
            // update 'dataUploaded' flag:
            sharedData->dataUploaded = true;
            // create an instance of Knn:
            sharedData->k_model = Knn(sharedData->distanceMetric, sharedData->k, sharedData->db_classified.db);
            // update that Knn instance have been initialized.
            sharedData->k_initialized = true;
            }
        }
}
/*This function executes command #2. it sends to the client the current settings
 * and enables changing them if requested*/
void Settings::execute(SharedData *sharedData) {
    string setting = "The current KNN parameters are: K = " + to_string(sharedData->k)+", distance metric = " + sharedData->distanceMetric+"\n#cmd2@@";
    dio->write(setting);
    string settingsInput=dio->read();
    settingsInput=settingsInput.substr(0,settingsInput.length()-1);
    // it means that user didn't press only "enter".
    if (settingsInput.length() != 0){
        string delim = " ";
        if(!(settingsInput.find(" ") != string::npos)){
            dio->write("invalid input\n@@");
            return;
        }
        if(&settingsInput[settingsInput.length()-1] != " ") {
            vector<string> settings = separateString(settingsInput, delim);
            // This case means that the user insert more than 2 parameters.
            if(settings.size() > 2){
                dio->write("invalid input\n@@");
                return;
            }
            // assign and check if k is valid.
            int k = checkPositiveInt(settings[0]);
            if (k == 0) {
                dio->write("invalid value for K\n@@");
                // check if also the metric is not valid.
                if (!checkMetric(settings[1])) {
                    dio->write("invalid value for metric\n@@");
                }
                    return;
            } else {
                // check if distance metric is valid.
                // the try and catch block is for the cases where the user inserts blank space after the k,
                // and not a Distance Metric alias.
                try {
                    if (!checkMetric(settings[1])) {
                        dio->write("invalid value for metric\n@@");
                        return;
                    }
                    else {
                        string distanceMetric = settings[1];
                        // change metric if it's different from the current setting.
                        if (distanceMetric != sharedData->distanceMetric)
                            sharedData->distanceMetric = distanceMetric;
                        sharedData->k_model.updateDistanceMetric(sharedData->distanceMetric);
                    }
                }
                catch (std::out_of_range& e){
                    dio->write("invalid input\n@@");
                    return;
                }
                // change k if it's different from the current setting.
                if (k != sharedData->k) {
                    // If the user inserted k larger than data size, we return invalid input.
                    if(k > sharedData->db_classified.db.size()){
                        dio->write("invalid value for K\n@@");
                        return;
                    }
                    else {
                        sharedData->k = k;
                        sharedData->k_model.updateK(sharedData->k);
                    }
                }
            }
        }

    }
}
/*This function executes command #3. it performs classification of the test file if the
 * 2 files are uploaded*/
void Classify::execute(SharedData *sharedData) {
    // First check if the data was uploaded.
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n#cmd3@@");
        return;
    }
    else{
        // classifying the data.
        sharedData->k_model.predict(sharedData->db_unclassified);
        dio->write("classifying data complete\n#cmd3@@");
        // set the flag to true.
        sharedData->dataClassified=true;
        return;
    }
}
/*This function executes command #4.It sends the client the classification results if the
   2 files are uploaded and if the data is classified.*/
void DisplayResults::execute(SharedData *sharedData) {
    // check if data is uploaded.
    if(!sharedData->dataUploaded){
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        dio->write("please upload data\n#cmd4@@");
        return;
    }

    else{
        // check if data was uploaded but not classified.
        if(!sharedData->dataClassified){
            dio->write("please classify the data\n#cmd4@@");
            return;
        }
            // in the case data was uploaded and classified.
        else{
            // print the labels after classification.
            string classifiedRow = "";
            for (int i =1 ; i < sharedData->db_unclassified.db.size()+1; i++) {
                classifiedRow += to_string(i) + "\t" + sharedData->db_unclassified.db[i - 1].label + "\n";
            }
            classifiedRow = classifiedRow + "Done.\n#cmd4@@";
            dio->write(classifiedRow);
        }
    }
}
/*This function sends the results of classification(if exists) to the client.*/
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
/*This function executes command number 5.
 it sends the results of classification(if exists) to the client.*/
void Download::execute(SharedData* sharedData) {
    // check if data is uploaded and classified:
    if(!sharedData->dataUploaded){
        dio->write("please upload data\n@@");
        return;
    }else if(!sharedData->dataClassified){
        dio->write("please classify the data\n@@");
        return;
    }else {
        // send the client an identifier of command 5:
        dio->write("#cmd5@@");
        // get an update about a valid path from client:
        string message = dio->read();
        if(message.find("*pathInserted")!= string::npos) {
            sendFile(sharedData);

        }
        return;
    }
}
/*This function executes the exit command which detouch the server from client*/
void Exit::execute(SharedData* sharedData){}