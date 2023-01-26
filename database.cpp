/*This class represents a database of a certain classification:*/
#include "database.h"

/*contractor:*/

/*This function create the class's members:  */
void DataBase::createDataBase(vector<vector<string> > readOutput,bool validFile,bool  classifiedFlag) {
    isClassified=classifiedFlag;
    isValid=validFile;
    //check if file is empty:
    if(readOutput.size()<=1){
       isValid=false;
    }
    //check that file is in the right format:
    if (!doubleValidation(readOutput[0][0])){
        isValid=false;
    }
    //loop over the 2D vector that contains the file's data:
    for(int i=0;i<readOutput.size();i++)
    {
        //initialize a struct that will contain numbers, size and label:
        object obj;
        for(int j=0;j<readOutput[i].size();j++)
        {
            //if we are not in the last column:
            if (j!=readOutput[i].size()-1){
                //check that the number is valid
                if(!doubleValidation(readOutput[i][j])){
                  isValid=false;
                }
                double num=stod(readOutput[i][j]);
                //push the number into the values vector:
                obj.values.push_back(num);
            }else{
                //if we got to the last column-check if the file is classified:
                if(isClassified) {
                    obj.label = readOutput[i][j];
                    obj.size = j;
                    db.push_back(obj);
                }else{
                    double num=stod(readOutput[i][j]);
                    //push the number into the values vector:
                    obj.values.push_back(num);
                    obj.label = "None";
                    obj.size = j;
                    db.push_back(obj);
                }
            }
        }

    }
}

