#include "header.h"

void print_double(double num)
{
    if (floor(num) == ceil(num))
    {
        cout.precision(1);
        cout << fixed << num << endl;
    }
    else
    {
        cout.precision(5);
        cout << fixed << num << endl;
    }
}