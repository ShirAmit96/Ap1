#include "ManageInput.h"
#include "header.h"

class ManageInput{
public:
    ManageInput(){
    }

private:
    vector<string> getFirstInput(char [] input){
        vector <string> inputVec {};
        vecor <string> finalVec{};
        for(int i=1;i<input.length()){
            inputVec.push_back(input[i]);
        }
        InputCheck Check=InputCheck::();
        finalVec=Check.stringsValidation(inputVec);
        return finalVec;
    }
    vector<double> getSecondInput(){
        string input;
        getline(cin, input);
        InputCheck Check=InputCheck::();
        vector<double> finalVec=Check.createNumbersVec(input);
        return finalVec;

    }


}