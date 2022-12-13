/*This class manages the input sends it to input_validation class. */
#include "input_managment.h"
/*This function gets a string vector and returns the string if it is valid*/
vector<string> getFirstInput(vector<string> inputVec) {
    vector<string> finalVec{};
    //send the input to a validation check function:
    finalVec = stringsValidation(inputVec);
    //return a valid vector:
    return finalVec;
}
vector<double> getSecondInput(){
    //get input from the user
    string input;
    getline(cin, input);
    //send the input to a validation check:
    vector<double> numsVec=createNumbersVec(input);
    //return a valid input:
    return numsVec;

}
