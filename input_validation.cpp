#include "input_validation.h"
/*This function separates the input string into sub strings by
 space delimiter and returns a vector of these sub strings */

vector<string> separateString(string input, string delim)
{
    /*define space to be the delimiter and initialize the sub strings vector:*/
    size_t delimIndex = 0;
    vector<string> subStrVec{};
    string subStr;
    /*Loop over the input string and each time you find a space do the following:*/
    while ((delimIndex = input.find(delim)) != string::npos)
    {
        /*Define a sub string that goes from index 0 of the input string until the space index:*/
        subStr = input.substr(0, delimIndex);
        /*Erase the substring that we just saved from the input string:*/
        input.erase(0, delimIndex + delim.length());
        /*Push the sub string into the sub strings vector:*/
        subStrVec.push_back(subStr);
    }
    /*Push the last sub string to the sub strings vector:*/
    subStrVec.push_back(input);
    /*Return the sub strings vector: */
    return subStrVec;
}

vector<string> separateByAlpha(string input){
    int delimIndex=0;
    for (int i=0; i<input.length();i++){
        if (isalpha(input[i])&&input[i-1]==' '){
            delimIndex=i-1;
            string firstStr=input.substr(0, delimIndex);
            string secStr= input.substr(i,input.length());
            vector <string> inputVec {};
            inputVec.push_back(firstStr);
            inputVec.push_back(secStr);
            return inputVec;
        }
    }
}

int checkK(string k){
    int new_k;
    try{
         new_k=stoi(k);
    }catch(...){

    }
    if(new_k>0){
        return new_k;
    }

}
bool ipCheck(string ip){
    vector<string> ipVec= separateString(ip,".");
    for (int i = 0; i < ipVec.size(); i++) {
        if (ipVec[i].length() > 3
            || stoi(ipVec[i]) < 0
            || stoi(ipVec[i]) > 255) {
            return 0;
        }

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
    return 1;
}

/*This function check if a given string represents a double.
 if so it returns a double.*/
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
            i+=2;
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
    //This vector will be the vector returned if the unput is not valid:
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

bool validPort(int serverPort){
    if((serverPort<1024)||(serverPort>65535)){
        return false;
    }
    else{
        return true;
    }
}

// this function making sure that a given file name is of csv file.
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



