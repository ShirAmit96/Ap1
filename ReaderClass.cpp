#include "ReaderClass.h"

ReaderClass::ReaderClass(string name){
    setFilesNames(name);
    setFilePath();
}

void ReaderClass::setFilesNames(string name){
    fileName=name;
    dataSets="DataSets";
    if(fileName=="iris_classified.csv"){
        dataType="iris";
    }else if(fileName=="beans_classified.csv"){
        dataType="beans";
    }else{
        dataType="wine";
    }

}
void ReaderClass::setFilePath(){
    path="../"+dataSets+"/"+dataType+"/"+fileName;
}
DataBase ReaderClass::readCsv(){
    vector<vector<string>> content;
    vector<string> row;
    string line,word;


    //ios::in allows input (read operations) from a stream.
    fstream file (path, ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while(getline(str, word, ',')) {
                row.push_back(word);

            }
            content.push_back(row);
        }
        DataBase db=DataBase(content);
        return db;
    }

    else
        cout<<"Could not open the file\n";

}