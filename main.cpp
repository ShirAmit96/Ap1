#include "header.h"
using namespace std;

int main()
{
    /*Get input of two vectors from the user and
     create number's vectors from the input:*/
    vector<double> x_vector{};
    x_vector = get_input();
    vector<double> y_vector{};
    y_vector = get_input();
    /*If the 2 vectors are valid print the result of all the distance functions:*/
    if (vectors_check(x_vector, y_vector) == true)
    {
        print_double(euclidean_distance(x_vector, y_vector));
        print_double(manhattan_distance(x_vector, y_vector));
        print_double(chebyshev_distance(x_vector, y_vector));
        print_double(canberra_distance(x_vector, y_vector));
        print_double(minkowsky_distance(x_vector, y_vector));
    }
    return 1;
}