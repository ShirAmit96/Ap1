#include <cmath>
#include <iostream>
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