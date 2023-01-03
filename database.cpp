/*This class represents a database of a certain classification:*/
#include "database.h"

/*contractor:*/
DataBase::DataBase(vector<vector<string> > readOutput){
    createDataBase(readOutput);
}
/*This function create the class's members:  */
void DataBase::createDataBase(vector<vector<string> > readOutput) {
    if(readOutput.size()==0){
        cout<<"invalid file, exiting program"<<endl;
        exit(-1);
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
                    cout<<"invalid file, exiting program"<<endl;
                    exit(-1);
                }
                double num=stod(readOutput[i][j]);
                //push the number into the values vector:
                obj.values.push_back(num);
            }else{
                //if we got to the last column-initialize the label:
                obj.label=readOutput[i][j];
                obj.size=j;
                db.push_back(obj);

            }
        }

    }
}
