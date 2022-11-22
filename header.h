// Name: Guy Leib and Shir Amit
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
double general_dist_func(vector<double> x, vector<double> y, double p);
double euclidean_distance(vector<double> x, vector<double> y);
double manhattan_distance(vector<double> x, vector<double> y);
double minkowsky_distance(vector<double> x, vector<double> y);
double chebyshev_dis(vector<double> x, vector<double> y);
double canberra_dis(vector<double> x, vector<double> y);
vector<string> seperate_string(string input);
vector<double> nums_check(vector<string> x_vector);
bool vectors_check(vector<double> x, vector<double> y);
void get_input(vector<double>& x_vector, vector<double>& y_vector);