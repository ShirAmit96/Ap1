#include "main.h"
#include "knn.h"

int main(int argc, char *argv[])
{
    vector<string> inputVec{};
    for(int i=0;i<argc;i++){
        inputVec.push_back(argv[i]);
    }
    knnInput input=inputForKnn(inputVec);
    Knn k_model = Knn(input);
    string label =k_model.predict(numsVector);
    cout << label <<endl;
    return 1;
}