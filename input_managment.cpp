#include "input_managment.h"

vector<string> getFirstInput(vector<string> inputVec) {
    vector<string> finalVec{};
    finalVec = stringsValidation(inputVec);
    return finalVec;
}
vector<double> getSecondInput(){
    string input;
    getline(cin, input);
    vector<double> numsVec=createNumbersVec(input);
    return numsVec;

}
