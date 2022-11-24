
#include "header.h"

/*This function seperates the input string into sub strings by space delimiter and returns a vector of these sub strings */
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
/*This function checks if the vector includes only numbers and returns a doubles vector.
 if it includes a non number type it returns an empty vector.*/
vector<double> numsCheck(vector<string> xVector)
{
    /*This vector will be the returned vector if all the strings in the input are valid:*/
    vector<double> numVector{};
    /*This vector(an empty vector) will be the returned vector if there is at least one
    invalid string in the input:*/
    vector<double> emptyVector{};
    /*Iterate over all the vector's strings:*/
    for (auto x : xVector)
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
/*This function check if 2 vectors are not empty and if they are in the same size*/
bool vectorsCheck(vector<double> x, vector<double> y)
{
    if (x.size() == y.size() && x.size() != 0)
    {
        return true;
    }
    else
    {
        cout << "Input is not valid, exiting program" << endl;
        return false;
    }
}
/*This function gets an input fro the user and send the input to validation check functions.
the function returns a doubles vector. */
vector<double> getInput()
{
    /*Get input from the user:*/
    string x;
    cout << "Please enter vector: ";
    getline(cin, x);
    /*Seperate the input string into sub strings by space delimiter:*/
    vector<string> strVec1 = seperateString(x);
    /*Check that all the strings are valid and convert them into numbers:*/
    vector<double> numVec1 = numsCheck(strVec1);
    /*Return the numbers vector:*/
    return numVec1;
}