//
// Created by 97252 on 11/01/2023.
//

#include "uploadCSV.h"

void UploadCSV::execute() {
    dio->write("Please upload your local train CSV file.\n");
    string trainFile=dio->read();
    dio->write("Please upload your local test CSV file.\n");
    string testFile=dio->read();
}