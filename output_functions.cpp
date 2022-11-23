#include "header.h"
/*This function  prints a double in a precusion of  only one numbber after the dot if its a natural number.
 else- it prints the number in a precision of 5 numbers after the dot. */
void print_double(double num)
{
    /* If rounding down is equal to rounding up- the number is natural number:*/
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