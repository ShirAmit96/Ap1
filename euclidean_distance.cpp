#include "general_dist_func.cpp"
#include <vector>
float euclidean_distance(fvector<float> x, vector<float> y){
    return general_dist_func(x,y,2);
}