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
    //vector <double> numsVector=MngInput.getSecondInput();
    ReaderClass read("iris_classified.csv");
    read.readCsv();
    return 1;
}