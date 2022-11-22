#include <iostream>
#include <cmath>
#include <vector>
#include "header.h"
using namespace std;

int main()
{
    vector<double> x_vector{};
    x_vector = get_input();
    vector<double> y_vector{};
    y_vector = get_input();
    if (vectors_check(x_vector,y_vector) == true){
        cout.precision(1);
        cout << fixed << euclidean_distance(x_vector, y_vector)<<endl;
        cout << manhattan_distance(x_vector, y_vector)<<endl;
        cout << chebyshev_distance(x_vector, y_vector)<<endl;
        cout << canberra_distance(x_vector, y_vector)<<endl;
        cout << minkowsky_distance(x_vector, y_vector)<<endl;
    }
    return 1;
}