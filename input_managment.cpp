/*This class manages the input sends it to input_validation class. */
#include "input_managment.h"
/*This function gets a string vector and returns the string if it is valid*/
void getFirstInput(vector<string> inputVec) {
    //check input size:
    if(inputVec.size()!=3){
        cout<<"invalid input size"<<endl;
        exit(-1);
    }
    //check if ip is valid
    if(ipCheck(inputVec[1])==0) {
        cout << "invalid input" << endl;
        exit(-1);
    }
        //add guy's input check for the port
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

bool getClientInput(string input){
    //separate into two strings by  a letter delimiter:
    vector<string> inputVec= separateByAlpha(input);
    //check if the nums vector is valid:
    if (createNumbersVec(inputVec[0]).size()==0){
        cout<<"vector error"<<endl;
        return 0;
    }
    return 1;
}


//
//int separateServerInput(string input, char* buffer, vector<double> &vec, int &k, string &distanceMetric){
//    //separate into two strings by  a letter delimiter:
//    vector<string> inputVec= separateByAlpha(input);
//    createNumbersVec(inputVec[0]).size();
//
//    return 1;
//}
