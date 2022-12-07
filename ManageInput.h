#ifndef AP1_MANAGEINPUT_H
#define AP1_MANAGEINPUT_H
#include <string>
#include <vector>
#include <iostream>
#include "InputCheck.h"
using namespace std;

class ManageInput {
private:
    vector<string> finalVec;
    vector<double> numsVec;
public:
    ManageInput();
    vector<string> getFirstInput(vector<string> inputVec);
    vector<double> getSecondInput();
};
#endif //AP1_MANAGEINPUT_H
