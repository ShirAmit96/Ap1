#include "header.h"
#include "InputCheck.h"

class InputCheck{
private:
    string input;
public:
    InputCheck(string i){
        this->input=i;
    }
private:
    vector<string> seperateString(string input) {
    /*define space to be the delimiter and initialize the sub strings vector:*/
    string delim = " ";
    size_t delimIndex = 0;
    vector<string> subStrVec{};
    string subStr;
    /*Loop over the input string and each time you find a space do the following:*/
    while ((delimIndex = input.find(delim)) != string::npos) {
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
    vector<string> stringsValidation( vector<string> inputVec){
        vector<string> finalVec{};
        vector<string> emptyVec{};
        string k=inputVec[1];
        string file=inputVec[2];
        string distanceMet=inputVec[3];
        if (inputVec.size()!=4){
            cout<<"Error: invalid number of arguments"<<endl;
            return emptyVec;
        }
        if(k[0]!='0'&& isdigit(k[0])){
            for(auto c:k){
                if(!isdigit(c)){
                    cout<<"Error: k value is invalid."<<endl;
                    return emptyVec;
                }
            }
            finalVec.push_back(k);
        }
        if(file=="iris_classified.csv"||file=="beans_classified.csv"||file=="wine_classified.csv"){
            finalVec.push_back(file);
        }else{
            cout<<"Error: file name is invalid."<<endl;
            return emptyVec;
        }
        if(distanceMet=="AUC"||distanceMet=="CHB"||distanceMet=="MAN"
        ||distanceMet=="CAN"||distanceMet=="MIN"){
            finalVec.push_back(distanceMet);
        }
        else{
            cout<<"Error: distance metric name is invalid."<<endl;
            return emptyVec;
        }
        return finalVec;
    }

    vector<double> vectorValidation( vector<string> inputVec){
        /*This vector will be the returned vector if all the strings in the input are valid:*/
        vector<double> numVector{};
        /*This vector(an empty vector) will be the returned vector if there is at least one
        invalid string in the input:*/
        vector<double> emptyVector{};
        /*Iterate over all the vector's strings:*/
        for (auto x : inputVec)
        {
            /*If the stirngs contains only one digit number put it immediately in the numbers vector
             and continue to the next string:*/
            if (isdigit(x[0]) && x.length() == 1)
            {
                double num = stof(x);
                numVector.push_back(num);
                continue;
            }
                /*If the strings starts with a 0 but doesent have a dot after it- the string is not valid.
                 return an empty vector*/
            else if (x[0] == '0' && x[1] != '.')
            {
                return emptyVector;
            }
            /*else- for now the string is valid but put a flag in order to indicate
             we already have one dot(more than one dot-not valid):*/
            bool dotFlag = false;
            /*Iterate over all the chars of each stirng:*/
            for (int i = 0; i < x.length(); i++)
            {
                /*If we got to the last char and it is a digit- put the string in the nums vector:*/
                if (isdigit(x[i]) && (i == x.length() - 1))
                {
                    double num = stod(x);
                    numVector.push_back(num);
                }
                    /*If the char in index i is a digit-continue to the next one: */
                else if (isdigit(x[i]))
                {
                    continue;
                }
                    /*Handle a negative number case:*/
                else if (x[0] == '-' && x.length() > 1)
                {
                    /*Prevent a "--" case:*/
                    if (x[1] == '-')
                    {
                        return emptyVector;
                    }
                }
                    /*Handle a float case:*/
                else if (x[i] == '.')
                {
                    /*Prevent a case of more than one dot:*/
                    if (dotFlag == false)
                    {
                        dotFlag = true;
                        continue;
                    }
                        /*More than one dot case- return empty vector:*/
                    else
                    {
                        return emptyVector;
                    }
                }
                else
                {
                    return emptyVector;
                }
            }
        }
        return numVector;
    }
};

