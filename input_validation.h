
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
bool checkMetric(string metric);
int checkPositiveInt(string num);
int validPort(string serverPort);
bool validFile(string fileName);
void checkFirstInput(vector<string> inputVec);
bool checkUserInput(string input);

#endif //AP1_INPUT_VALIDATION_H
