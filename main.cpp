#include "main.h"
using namespace std;

int main(int argc, char *argv[])
{
    vector<string> inputVec{};
    for(int i=0;i<argc;i++){
        inputVec.push_back(argv[i]);
    }

    ManageInput MngInput;
    vector<string>  firstInput=MngInput.getFirstInput(inputVec);
    vector <double> numsVector=MngInput.getSecondInput();
    if(firstInput.size()!=0 && numsVector.size()!=0) {
        int k =stoi(firstInput[0]);
        string fileName = firstInput[1];
        string distanceMet = firstInput[2];
        ReaderClass read(fileName);
        DataBase db=read.readCsv();
        //guy: you should call here to knn and  enter to Knn-> "k","distanceMet", "db",  and "numsVector"
    }else{
        cout<<"Exiting program...";
        return 0;
    }

    return 1;
}