#ifndef AP1_KNN_H
#define AP1_KNN_H

#include "distance_metric.h"
using namespace std;
class Knn {
    DistanceMetric* metric;
    int k;
    string distanceMetric;

    vector<double> distance(vector<vector<double>> database, vector<double> x);

    vector<string> nearestKNeighbors();

    string mostCommonLabel();

public:
    Knn(string metric, int k);
    string predict(vector<vector<double>> database, vector<double> x);
};
#endif //AP1_KNN_H
