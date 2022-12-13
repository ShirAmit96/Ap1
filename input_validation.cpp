#include "input_validation.h"
/*This function separates the input string into sub strings by
 space delimiter and returns a vector of these sub strings */
vector<string> seperateString(string input)
{
    /*define space to be the delimiter and initialize the sub strings vector:*/
    string delim = " ";
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
/*This function checks if the args input is valid.
 if so, it returns a vector of the given args.*/
vector<string> stringsValidation( vector<string> inputVec){
	   //if args size!=4, terminate program:
    if (inputVec.size()!=4){
        cout<<"Error: invalid number of arguments, exiting program..."<<endl;
        exit(0);
    }
    vector<string> finalVec{};
    string k=inputVec[1];
    string file=inputVec[2];
    string distanceMet=inputVec[3];
    //check that  k is  a positive int:
    if(k[0]!='0'&& isdigit(k[0])){
        for(auto c:k){
            //if k is not valid-terminate program:
            if(!isdigit(c)){
                cout<<"Error: k value is invalid, exiting program..."<<endl;
                exit(-1);
            }
        }
        //push k to the final vector:
        finalVec.push_back(k);
    }else{
        //if k is not valid-terminate program:
        cout<<"Error: k value is invalid, exiting program..."<<endl;
        exit(-1);
    }
    //check if the inserted file name is valid:
    if(file=="iris_classified.csv"||file=="beans_Classified.csv"||file=="wine_Classified.csv"){
        finalVec.push_back(file);
    }else{
        //if file name is not valid-terminate program:
        cout<<"Error: file name is invalid,exiting program..."<<endl;
        exit(-1);
    }
    //check if the inserted distance metric is valid:
    if(distanceMet=="AUC"||distanceMet=="CHB"||distanceMet=="MAN"
       ||distanceMet=="CAN"||distanceMet=="MIN"){
        finalVec.push_back(distanceMet);
    }
    else{
        //if name of the distance metric is not valid-terminate program:
        cout<<"Error: distance metric name is invalid, exiting program..."<<endl;
        exit(-1);
    }
    //if al the parameters are valid-return the final vector:
    return finalVec;
}
/*This function check if a given string represents a double.
 if so it returns a double.*/
double doubleValidation(string  s){
    //If the string contains only one digit number:
    if (isdigit(s[0]) && s.length() == 1)
    {
        // convert the string to a double:
        double num = stod(s);
        return num;

    }
    //If the string starts with a 0 but doesn't have a dot after it-exit program:
    else if (s[0] == '0' && s[1] != '.')
    {
        cout<<"Error: an invalid data was found, exiting program..."<<endl;
        exit(-1);
    }
    //put a flag in order to indicate we already have one dot:
    bool dotFlag = false;
    //Iterate over all the chars of each string:
    for (int i = 0; i < s.length(); i++)
    {
        //If we got to the last char and it is a digit:
        if (isdigit(s[i]) && (i == s.length() - 1))
        {
            //convert the string to a double:
            double num = stod(s);
            //return the double:
            return num;
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
                cout<<"Error: an invalid data was found, exiting program..."<<endl;
                exit(-1);
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
                cout<<"Error: an invalid data was found, exiting program..."<<endl;
                exit(-1);
            }
        }
        else
        {
            cout<<"Error: an invalid data was found, exiting program..."<<endl;
            exit(-1);
        }
    }
}
/*This function gets a string vector,
 checks if all the items in the vector are doubles and return a double vector*/
vector<double> vectorValidation( vector<string> inputVec){
    /*This vector will be the returned vector if all the strings in the input are valid:*/
    vector<double> numVector{};
    /*Iterate over all the vector's strings:*/
    for (auto x : inputVec)
    {
        //check if the string represents a double and save the double:
        double num=doubleValidation(x) ;
        //push the double to a vector:
        numVector.push_back(num);

    }
    return numVector;
}
/*This function gets a string, separates the string by space delimiter,
 checks if the sub strings are valid numbers and return a double's vector. */
vector<double> createNumbersVec(string input){
    //send the string to a function that will separate it by space:
    vector<string> inputVec=seperateString(input);
    //send the vector to a function that makes sure it contains valid numbers:
    vector<double> finalVec=vectorValidation(inputVec);
    return finalVec;
}


