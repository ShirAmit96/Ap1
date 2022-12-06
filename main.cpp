#include "header.h"


using namespace std;

int main(int argc, char *argv[])
{
    ManageInput MngInput=ManageInput::();
    vector<string>  firstInput=MngInput.getfirstInput(argv);
    vector <double> numsVector=MngInput.getSecondInput();
    return 1;
}