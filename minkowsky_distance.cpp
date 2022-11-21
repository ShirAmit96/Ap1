#include "general_dist_func.cpp"
#include <vector>
float minkowsky_distance(vector<float> x, vector<float> y){
    return general_dist_func(x,y,3);
}
