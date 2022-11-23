#include "header.h"
using namespace std;

int main()
{
    /*Get input of two vectors from the user and
     create number's vectors from the input:*/
    vector<double> x_vector{};
    x_vector = getInput();
    vector<double> y_vector{};
    y_vector = getInput();
    /*If the 2 vectors are valid print the result of all the distance functions:*/
    if (vectorsCheck(x_vector, y_vector) == true)
    {
        printDouble(euclideanDistance(x_vector, y_vector));
        printDouble(manhattanDistance(x_vector, y_vector));
        printDouble(chebyshevDistance(x_vector, y_vector));
        printDouble(canberraDistance(x_vector, y_vector));
        printDouble(minkowskyDistance(x_vector, y_vector));
    }
    return 1;
}