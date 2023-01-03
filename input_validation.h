
#ifndef AP1_INPUT_VALIDATION_H
#define AP1_INPUT_VALIDATION_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<string> separateString(string input, string delim);
vector<string> separateByAlpha(string input);
bool ipCheck(string ip);
bool doubleValidation(string s);
vector<double> vectorValidation( vector<string> inputVec);
vector<double> createNumbersVec(string input);
int checkK(string k);
bool validPort(int serverPort);
bool validFile(string fileName);

#endif //AP1_INPUT_VALIDATION_H
