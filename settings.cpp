
#include "settings.h"
#include "input_validation.h"

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