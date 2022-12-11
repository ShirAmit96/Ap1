#include "DataBase.h"

DataBase::DataBase(vector<vector<string>> readOutput){
    createDataBase(readOutput);
}
void DataBase::createDataBase(vector<vector<string>> readOutput) {
    for(int i=0;i<readOutput.size();i++)
    {
        object obj;
        for(int j=0;j<readOutput[i].size();j++)
        {

            if (j!=readOutput[i].size()-1){
                double num=doubleValidation(readOutput[i][j]);
                obj.values.push_back(num);
            }else{
                obj.label=readOutput[i][j];
                obj.size=j;
                db.push_back(obj);

            }
        }

    }
}
