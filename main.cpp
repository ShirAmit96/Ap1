#include "main.h"
#include "knn.h"

int main(int argc, char *argv[])
{
    vector<string> inputVec{};
    for(int i=0;i<argc;i++){
        inputVec.push_back(argv[i]);
    }

    ManageInput MngInput;
    vector<string>  firstInput=MngInput.getFirstInput(inputVec);
    //vector <double> numsVector=MngInput.getSecondInput();
    vector <double> numsVector={6.9,3.1,4.9,1.5};
    if(firstInput.size()!=0 && numsVector.size()!=0) {
        int k =stoi(firstInput[0]);
        string fileName = firstInput[1];
        string distanceMet = firstInput[2];
        ReaderClass read(fileName);
        DataBase db=read.readCsv();
        Knn k_model = Knn(distanceMet,k,db.db);
        string label =k_model.predict(numsVector);
        cout << label <<endl;
    }else{
        cout<<"Exiting program...";
        return 0;
    }
    return 1;
}