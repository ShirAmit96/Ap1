#include <iostream>
#include <cmath>
#include <vector>
#include "header.h"
using namespace std;

int main()
{
    vector<double> x_vector{};
    vector<double> y_vector{};
    get_input(x_vector,y_vector);
    // for (int i = 1; i < 4; i++)
    // {
    //     x_vector.push_back(i);
    //     y_vector.push_back(4 - i);
    // }

    cout << chebyshev_dis(x_vector, y_vector);

    return 1;
}