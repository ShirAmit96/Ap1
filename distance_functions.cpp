#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

float general_dist_func(vector<float> x, vector<float> y, float p){
    int z = 0;
    // add a for loop that adds zero to the smaller array in case of not equal len. 
    //int len = min(sizeof(vector1),sizeof(vector2));
    for (int i = 0 ; i<x.size();i++){
        z += pow((abs(x[i]-y[i])),p);
    }
    return pow(z,(1/p));
}

float euclidean_distance(vector<float> x, vector<float> y){
    return general_dist_func(x,y,2);
}

float manhattan_distance(vector<float> x, vector<float> y){
    return general_dist_func(x,y,1);
}

float minkowsky_distance(vector<float> x, vector<float> y){
    return general_dist_func(x,y,3);
}


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
