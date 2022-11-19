#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

float chebyshev_dis(vector<float> x, vector<float> y)
{
    float max = 0;
    float sub_abs = 0;
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
