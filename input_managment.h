#ifndef AP1_INPUT_MANAGMENT_H
#define AP1_INPUT_MANAGMENT_H
#include "database.h"
#include "reader_class.h"
#include "input_validation.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


void getFirstInput(vector<string> inputVec);
vector<double> getSecondInput();
bool getClientInput(string input);
#endif //AP1_INPUT_MANAGMENT_H
