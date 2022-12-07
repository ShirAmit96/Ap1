#ifndef AP1_INPUTCHECK_H
#define AP1_INPUTCHECK_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class InputCheck{
public:
    InputCheck();
    vector<string> seperateString(string input);
    vector<string> stringsValidation( vector<string> inputVec);
    vector<double> vectorValidation( vector<string> inputVec);
    vector<double> createNumbersVec(string input);

};

#endif //AP1_INPUTCHECK_H
