#include "main.h"

int main(int argc, char *argv[])
{
    //create a vector from args in order to send it to a validation check:
    vector<string> inputVec{};
    for(int i=0;i<argc;i++){
        inputVec.push_back(argv[i]);
    }
    //check if the vector is valid and if so -return it:
    vector <string> firstInput= getFirstInput(inputVec);
    //create input for knn:
    int k =stoi(firstInput[0]);
    string fileName = firstInput[1];
    string distanceMet = firstInput[2];
    //Read the requested input file:
    ReaderClass read=ReaderClass(fileName);
    DataBase db=read.readCsv();
    int columnsSize=db.db[0].size;
	//create a knn class :
	 Knn k_model = Knn(distanceMet, k, db.db);
    //check if k is not too big:
    if(k>db.db.size()){
        cout<<"Error: k value is bigger than data's size, exiting program..."<<endl;
        exit(-1);
    }
	while(true){
		//get vector from the user and check if it is valid:
		vector <double> secondInput= getSecondInput();
		//Check if the inserted vector corresponds in size to the number of columns:
		if(columnsSize==secondInput.size()){
			//predict the label using knn class:  
			string label =k_model.predict(secondInput);
			cout << label <<endl;
		}else{
			cout<<"Error: the inserted vector is not valid,Exiting program..."<<endl;
			exit(-1);
		}
	}
    return 1;
}
