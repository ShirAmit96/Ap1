#include "header.h"
using namespace std;

int main()
{
    vector<double> x_vector{};
    x_vector = get_input();
    vector<double> y_vector{};
    y_vector = get_input();
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