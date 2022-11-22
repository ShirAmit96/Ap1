#include <iostream>
#include <cmath>
#include <vector>
#include "header.h"
using namespace std;

double general_dist_func(vector<double> x, vector<double> y, double p)
{
    int z = 0;
    for (int i = 0; i < x.size(); i++)
    {
        z += pow((abs(x[i] - y[i])), p);
    }
    return pow(z, (1 / p));
}

double euclidean_distance(vector<double> x, vector<double> y)
{
    return general_dist_func(x, y, 2);
}

double manhattan_distance(vector<double> x, vector<double> y)
{
    return general_dist_func(x, y, 1);
}

double minkowsky_distance(vector<double> x, vector<double> y)
{
    return general_dist_func(x, y, 3);
}

double chebyshev_distance(vector<double> x, vector<double> y)
{
    double max = 0;
    double sub_abs = 0;
    for (int i = 0; i < x.size(); ++i)
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

double canberra_distance(vector<double> x, vector<double> y)
{
    double sub_abs = 0;
    double sum_abs = 0;
    double sigma = 0;
    for (int i = 0; i < x.size(); ++i)
    {
        sub_abs = abs(x[i] - y[i]);
        sum_abs = abs(x[i]) + abs(y[i]);
        if (sum_abs != 0)
        {
            sigma += (sub_abs / sum_abs);
        }
    }
    return sigma;
}