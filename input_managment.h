//
// Created by 97252 on 11/12/2022.
//

#ifndef AP1_INPUT_MANAGMENT_H
#define AP1_INPUT_MANAGMENT_H
#include "input_validation.h"
#include <string>
#include <vector>
#include <iostream>
#include "DataBase.h"
#include "ReaderClass.h"
struct knnInput{
    string metricInput;
    int k;
    vector<DataBase::object> db;
};
using namespace std;
vector<string> getFirstInput(vector<string> inputVec);
vector<double> getSecondInput();
knnInput inputForKnn(vector<string> inputVec);
#endif //AP1_INPUT_MANAGMENT_H
