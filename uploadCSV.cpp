//
// Created by 97252 on 11/01/2023.
//

#include "uploadCSV.h"
#include "knn.h"

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
                if (!read2.validFile||dbUnclassified.db.size!=dcClassified.db.size) {
                    dio->write("invalid input.\n");
                    return;
                } else {
                    sharedData->db_classified = dbClassified;
                    sharedData->db_unclassified = dbUnclassified;
                    sharedData->dataUploaded=true;
                    dio->write("Upload complete.");
                    // create an instance ok Knn
                    sharedData->k_model = Knn(sharedData->distanceMetric, sharedData->k, sharedData->db_classified.db);
                    // update that Knn instance have been initialized.
                    sharedData->k_initialized=true;
                }
            }
        }
    }
}