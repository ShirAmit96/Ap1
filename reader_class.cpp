/*This class reads a csv file and creates a DataBase class.*/
#include "reader_class.h"
/*Constructor:*/
ReaderClass::ReaderClass(string name){
    fileName=name;
}
/*This function reads a CSV file and creates a DataBase class that contains the file's Data:*/
DataBase ReaderClass::readCsv(){
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
                cout<<"Error:Invalid classification file,exiting program..."<<endl;
                exit(-1);
            }
            //If there is a line with a different number of columns than the rest of the file-exit:
            if(rowSize!=row.size()){
              cout<<"Error:Invalid classification file, exiting program..."<<endl;
              exit(-1);
            }else {
                //if the number of columns is fine-insert the "row" vector into "content" vector:
                content.push_back(row);
                counter++;
            }
        }
        file.close();
        //check if file is empty:
        if(content.size()==0){
            cout<<"Invalid classification file, exiting program..."<<endl;
            exit(-1);
        }
        //create a DataBase class that contains the content of the file:
        DataBase db=DataBase(content);
        return db;
    }

    else
        cout<<"Could not open the file"<<endl;

}
