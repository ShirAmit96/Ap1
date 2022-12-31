#ifndef AP1_DISTANCE_METRIC_H
#define AP1_DISTANCE_METRIC_H
#include "iostream"
#include <string>
#include <vector>
#include <cmath>
using namespace std;
class DistanceMetric{
public:
    string metric;
    DistanceMetric(string distanceMetric);
    double calculate(vector<double> x, vector<double> y);
    double generalDistFunc(vector<double> x, vector<double> y, double p);
    double euclideanDistance(vector<double> x, vector<double> y);
    double manhattanDistance(vector<double> x, vector<double> y);
    double minkowskyDistance(vector<double> x, vector<double> y);
    double chebyshevDistance(vector<double> x, vector<double> y);
    double canberraDistance(vector<double> x, vector<double> y);
};
#endif //AP1_DISTANCE_METRIC_H
