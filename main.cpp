#include "header.h"
#include "distance_metric.cpp"
using namespace std;

int main()
{
    /*Get input of two vectors from the user and
     create number's vectors from the input:*/
    vector<double> xVector{};
    xVector = getInput();
    vector<double> yVector{};
    yVector = getInput();
    /*If the 2 vectors are valid print the result of all the distance functions:*/
    if (vectorsCheck(xVector, yVector) == true)
    {
        printDouble(euclideanDistance(xVector, yVector));
        printDouble(manhattanDistance(xVector, yVector));
        printDouble(chebyshevDistance(xVector, yVector));
        printDouble(canberraDistance(xVector, yVector));
        printDouble(minkowskyDistance(xVector, yVector));
    }
    return 1;
}