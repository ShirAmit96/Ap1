#include "ManageInput.h"


ManageInput::ManageInput(){}

vector<string> ManageInput::getFirstInput(vector<string> inputVec) {
    vector<string> finalVec{};
    InputCheck Check;
    finalVec = Check.stringsValidation(inputVec);
    return finalVec;
}
vector<double> ManageInput::getSecondInput(){
    string input;
    getline(cin, input);
    InputCheck Check;
    vector<double> numsVec=Check.createNumbersVec(input);
    return numsVec;
}


