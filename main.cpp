#include "main.h"

int main(int argc, char *argv[])
{
    vector<string> inputVec{};
    for(int i=0;i<argc;i++){
        inputVec.push_back(argv[i]);
    }
    vector <string> firstInput= getFirstInput(inputVec);
    int k =stoi(firstInput[0]);
    string fileName = firstInput[1];
    string distanceMet = firstInput[2];
    ReaderClass read=ReaderClass(fileName);
    DataBase db=read.readCsv();
    int columnsSize=db.db[0].size;
    vector <double> secondInput= getSecondInput();
    if(columnsSize==secondInput.size()){
        Knn k_model = Knn(distanceMet, k, db.db);
        string label =k_model.predict(secondInput);
        cout << label <<endl;
    }else{
        cout<<"Error: vector's size does not match the DataBase,Exiting program..."<<endl;
        exit(1);
    }
    return 1;
}