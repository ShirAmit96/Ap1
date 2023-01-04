#include "input_validation.h"
/*This function separates the input string into sub strings by
 the inserted delimiter and returns a vector of these sub strings */
vector<string> separateString(string input, string delim)
{
    //Initialize the sub strings vector:
    size_t delimIndex = 0;
    vector<string> subStrVec{};
    string subStr;
    //Loop over the input string and each time you find the delimiter do the following:
    while ((delimIndex = input.find(delim)) != string::npos)
    {
        //Define a sub string that goes from index 0 of the input string until the delimiter index:
        subStr = input.substr(0, delimIndex);
        //Erase the substring that we just saved from the input string:
        input.erase(0, delimIndex + delim.length());
        //Push the sub string into the sub strings vector:
        subStrVec.push_back(subStr);
    }
    //Push the last sub string to the sub strings vector:
    subStrVec.push_back(input);
    //Return the sub strings vector:
    return subStrVec;
}
/*This function separates the input string into sub strings by
  a letter delimiter and returns a vector of these sub strings */
vector<string> separateByAlpha(string input){
    int delimIndex=0;
    for (int i=0; i<input.length();i++){
        //check if we got to a letter and before it a sapce:
        if (isalpha(input[i])&&input[i-1]==' '){
            delimIndex=i-1;
            //spilt the string into 2 sub strings:
            string firstStr=input.substr(0, delimIndex);
            string secStr= input.substr(i,input.length());
            //insert the 2 new strings into a vector and return it:
            vector <string> inputVec {};
            inputVec.push_back(firstStr);
            inputVec.push_back(secStr);
            return inputVec;
        }
    }
}
/*delete ♥♥♥♥*/
int checkK(string k){
    int new_k;
    try{
         new_k=stoi(k);
    }catch(...){
        new_k=0;
    }
    return new_k;
}
/*This function gets a string and check if it is a valid ip address:*/
bool ipCheck(string ip){
    //separate the string by a '.' delimiter:
    vector<string> ipVec= separateString(ip,".");

    for (int i = 0; i < ipVec.size(); i++) {
        //check if the sub string represents a number:
        if(!checkPositiveInt(ipVec[i])){
            if(ipVec[i]!="0"){
                return 0;
            }
        }
        //check if the string contains only 3 digits and the values are 0-255:
        if (ipVec[i].length() > 3
            || stoi(ipVec[i]) < 0
            || stoi(ipVec[i]) > 255) {
            return 0;
        }
        //if the string's length is>1 make sure it doesn't start with a '0':
        if (ipVec[i].length() > 1
            && stoi(ipVec[i]) == 0){
            return 0;
        }
        if (ipVec[i].length() > 1
            && stoi(ipVec[i]) != 0
            && ipVec[i][0] == '0') {
            return 0;
        }
    }
    //if al the validation checks passed - return true:
    return 1;
}
/*This function checks if a given string represents valid distance metric name*/
bool checkMetric(string metric){
    if(metric=="AUC"||metric=="MAN"||metric=="CHB"||metric=="CAN"||metric=="MIN"){
        return true;
    }
    return false;
}

/*This function check if a given string represents a double.
 if so it returns true.*/
bool doubleValidation(string  s){
    //If the string contains only one digit number:
    if (isdigit(s[0]) && s.length() == 1)
    {
        return 1;

    }
    //If the string starts with a 0 but doesn't have a dot after it-exit program:
    else if (s[0] == '0' && s[1] != '.')
    {
        return 0;
    }
    //put a flag in order to indicate we already have one dot:
    bool dotFlag = false;
    //Iterate over all the chars of each string:
    for (int i = 0; i < s.length(); i++)
    {
        //If we got to the last char and it is a digit:
        if (isdigit(s[i]) && (i == s.length() - 1))
        {
           return 1;
        }
        //If the char in index i is a digit-continue to the next one:
        else if (isdigit(s[i]))
        {
            continue;
        }
        //accept numbers that includes "E-"(but not on the first or last digit):
        else if(i!=0 && i!=s.length()-1 && s[i]=='E' &&s[i+1]=='-' &&isdigit(s[i+2])){
            i+=1;
            continue;
        }
        //Handle a negative number case:
        else if (s[0] == '-' && s.length() > 1)
        {
            //Prevent a "--" case:*/
            if (s[1] == '-')
            {
                return 0;
            }
        }
        //Handle a decimal number case:
        else if (s[i] == '.')
        {
            //Prevent a case of more than one dot:
            if (dotFlag == false)
            {
                dotFlag = true;
                continue;
            }
            //More than one dot case-return empty vector:
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
}
/*This function gets a string vector,
checks if all the items in the vector are doubles and return a double vector*/
vector<double> vectorValidation( vector<string> inputVec){
    //This vector will be the returned vector if all the strings in the input are valid:
    vector<double> numVector{};
    //This vector will be the vector returned if the input is not valid:
    vector<double> emptyVec{};
    //check if vector is empty:
    if (inputVec.size()==0){
       return emptyVec;
    }
    /*Iterate over all the vector's strings:*/
    for (auto x : inputVec)
    {
        //check if the string represents a double and save the double:
        if(doubleValidation(x)) {
            double num=stod(x);
            //push the double to a vector:
            numVector.push_back(num);
        }else{
            return emptyVec;
        }
    }
    return numVector;
}
/*This function gets a string, separates the string by space delimiter,
 checks if the sub strings are valid numbers and return a double's vector. */
vector<double> createNumbersVec(string input){
    //send the string to a function that will separate it by space:
    vector<string> inputVec=separateString(input, " ");
    //send the vector to a function that makes sure it contains valid numbers:
    vector<double> finalVec=vectorValidation(inputVec);
    return finalVec;
}
/*This function checks if a given string represents a valid port.
 * if it's a valid port it returns the port, else -it will return 0*/
int validPort(string serverPort){
    //make sure that the port is a positive number:
    int port= checkPositiveInt(serverPort);
    //make sure that the port is in the requested range:
    if((port<1024)||(port>65535)){
        return 0;
    }
    else{
        //if the port is valid return it:
        return port;
    }
}
/*This function checks if a given string represents a positive number.
 * if it's a positive number it returns it, else - it will return 0*/
int checkPositiveInt(string num) {
    int result;
    if (num[0] != '0' && isdigit(num[0])) {
        // loop over all the values of the string and make sure they are digits:
        for (auto n: num) {
            //if k is not valid-terminate program:
            if (!isdigit(n)) {
                return 0;
            }
        }
        //convert the string into an int:
        result = stoi(num);
        return result;
    }else {
        // if the string is not valid - return 0:
        return 0;
    }
}
/*This function making sure that a given file name is of csv file*/
bool validFile(string fileName){
    // finding the last position where there is a dot in the file name.
    size_t lastDot = fileName.find_last_of('.');
    // making sure that the dot is not the last char.
    if (lastDot == string::npos){
        return false;
    }
    string sub = fileName.substr(lastDot);
    if (sub == ".csv"){
        return true;
    }
    else{
        return false;
    }
}
/*This function checks if a given input vec contains valid ip and  valid port.
 * if the input is not valid -the client will be closed.*/
void checkFirstInput(vector<string> inputVec) {
    //check input size:
    if(inputVec.size()!=3){
        cout<<"invalid input size"<<endl;
        exit(-1);
    }
    //check if ip is valid:
    if(ipCheck(inputVec[1])==0) {
        cout << "invalid IP" << endl;
        exit(-1);
    }
    //check if the port is valid:
    if(validPort(inputVec[2])==0){
        cout << "invalid port" << endl;
        exit(-1);
    }

}

/*This function gets a string and checks if it includes a vector of numbers,
  a valid distance metric name and a valid k number.
 If all the conditions mentioned above are met the function will return true,
 else -it will return false..*/
bool checkUserInput(string input){
    //separate into two strings by  a letter delimiter:
    vector<string> inputVec= separateByAlpha(input);
    //check if the nums vector is valid:
    if (createNumbersVec(inputVec[0]).size()==0){
        return 0;
    }
    vector<string> secondVec= separateString(inputVec[1]," ");
    // Check if k is valid:
    int k=checkPositiveInt(secondVec[1]);
    if(k==0){
        return 0;
    }
    //Check if distance metric is valid:
    if(!checkMetric(secondVec[0])){
        return 0;
    }
    return 1;
}