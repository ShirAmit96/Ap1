
#ifndef AP1_INPUT_VALIDATION_H
#define AP1_INPUT_VALIDATION_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<string> seperateString(string input);
vector<string> stringsValidation( vector<string> inputVec);
double doubleValidation(string s);
vector<double> vectorValidation( vector<string> inputVec);
vector<double> createNumbersVec(string input);

#endif //AP1_INPUT_VALIDATION_H
