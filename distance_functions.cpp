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

float canberra_dis(vector<float> x, vector<float> y)
{
    float sub_abs = 0;
    float sum_abs = 0;
    float sigma = 0;
    for (int i = 0; i < x.size(); ++i)
    {
        sub_abs = abs(x[i] - y[i]);
        sum_abs = abs(x[i]) + abs(y[i]);
        sigma += (sub_abs / sum_abs);
    }
    return sigma;
}

int main()
{
    vector<float> x_vector{};
    vector<float> y_vector{};
    for (int i = 1; i < 4; i++)
    {
        x_vector.push_back(i);
        y_vector.push_back(4 - i);
    }

    cout << chebyshev_dis(x_vector, y_vector);

    return 1;
}
