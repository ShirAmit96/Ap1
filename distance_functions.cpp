#include "header.h"

/*This function is a generalized compute distance function and it'll
compute different distance depends on the p value that is passed -
if p=1 isthe distance is manhattan, if p=2 the distance is euclidean and for p>3 the distance is minkowsky*/
double general_dist_func(vector<double> x, vector<double> y, double p)
{
    int z = 0;
    for (int i = 0; i < x.size(); i++)
    {
        z += pow((abs(x[i] - y[i])), p);
    }
    return pow(z, (1 / p));
}
/*This function gets two vectors of double and returns the euclidean distance between them*/
double euclidean_distance(vector<double> x, vector<double> y)
{
    return general_dist_func(x, y, 2);
}
/*This function gets two vectors of double and returns the manhattan distance between them*/
double manhattan_distance(vector<double> x, vector<double> y)
{
    return general_dist_func(x, y, 1);
}
/*This function gets two vectors of double and returns the minikowsky distance between them*/
double minkowsky_distance(vector<double> x, vector<double> y)
{
    return general_dist_func(x, y, 3);
}
/*This function gets two vectors of double and returns the chebyshev distance between them*/
double chebyshev_distance(vector<double> x, vector<double> y)
{
    double max = 0;
    double sub_abs = 0;
    for (int i = 0; i < x.size(); ++i)
    /* for each value in the same index in the two vectors
    compute the absolute value of their subtraction and find the maximum between all*/
    {
        sub_abs = abs(x[i] - y[i]);
        if (i == 0)
        {
            max = sub_abs;
        }
        else if (sub_abs > max)
        {
            max = sub_abs;
        }
    }
    return max;
}
/*This function gets two vectors of double and returns the canberra distance between them*/
double canberra_distance(vector<double> x, vector<double> y)
{
    double sub_abs = 0;
    double sum_abs = 0;
    double sigma = 0;
    for (int i = 0; i < x.size(); ++i)
    {
        /*Compute the abslute value of each value
         and then subtract the values that are in the same index in the two vectors*/
        sub_abs = abs(x[i] - y[i]);
        /*Compute the abslute value of each value
          and then sum the values that are in the same index in the two vectors*/
        sum_abs = abs(x[i]) + abs(y[i]);
        /*If it's not a case of division by zero :add to the sigma variable the divison of the subtraction by the sum*/
        if (sum_abs != 0)
        {
            sigma += (sub_abs / sum_abs);
        }
    }
    return sigma;
}