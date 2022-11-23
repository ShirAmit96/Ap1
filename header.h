// Name: Guy Leib and Shir Amit
#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

using namespace std;
using namespace std;
double general_dist_func(vector<double> x, vector<double> y, double p);
double euclidean_distance(vector<double> x, vector<double> y);
double manhattan_distance(vector<double> x, vector<double> y);
double minkowsky_distance(vector<double> x, vector<double> y);
double chebyshev_distance(vector<double> x, vector<double> y);
double canberra_distance(vector<double> x, vector<double> y);
vector<string> seperate_string(string input);
vector<double> nums_check(vector<string> x_vector);
bool vectors_check(vector<double> x, vector<double> y);
vector<double> get_input();
void print_double(double num);