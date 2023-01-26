/*This class reads a csv file and creates a DataBase class.*/
#include "reader_class.h"
/*Constructor:*/
ReaderClass::ReaderClass(){
    validFile=true;
}
/*This function reads a CSV file and creates a DataBase class that contains the file's Data:*/
bool ReaderClass::isClassified(string fileType){
    if (fileType=="classified"){
        return true;
    }
    return false;

}
DataBase ReaderClass::readCsv(string fileName, string fileType){
    classifiedFlag=isClassified(fileType);
    vector<vector<string>> content;
    vector<string> row;
    string line,word;
    //ios::in allows input (read operations) from a stream:
    fstream file (fileName, ios::in);
    if(file.is_open())
    {
        int counter=0;
        int rowSize=0;
        while(getline(file, line))
        {
            //clear row vector from the former row:
            row.clear();
            //use "stringstream" in order to separate the line:
            stringstream str(line);
            //separate words by ',' delimiter:
            while(getline(str, word, ',')) {
                row.push_back(word);
            }
            //Determine the desired number of columns according to the first row:
            if(counter==0){
                rowSize=row.size();
            }
            if(row.size()==0){
                validFile=false;
                break;
            }
            //If there is a line with a different number of columns than the rest of the file-exit:
            if(rowSize!=row.size()){
                validFile=false;
                break;
            }else {
                //if the number of columns is fine-insert the "row" vector into "content" vector:
                content.push_back(row);
                counter++;
            }
        }
        file.close();
        //check if file is empty:
        if(content.size()==0){
            validFile=false;
        }
        //create a DataBase class that contains the content of the file:
        DataBase db;
        db.createDataBase(content, validFile, classifiedFlag);
        if(db.isValid&&validFile){
            validFile=true;
        }else{
            validFile=false;
        }
        return db;
    }
    //cant open file:
    else
        validFile=false;

}
