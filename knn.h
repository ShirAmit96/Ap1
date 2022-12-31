#ifndef AP1_KNN_H
#define AP1_KNN_H
#include "distance_metric.h"
#include "database.h"
#include<bits/stdc++.h>
using namespace std;
class Knn {


    vector<DataBase::object> db;

    vector<pair<double,string> > distance(vector<DataBase::object> database, vector<double> x);

    vector<string> nearestKNeighbors(vector<pair<double,string> > distancesAndLabels,int k);

    string mostCommonLabel(const vector<string> &labels);

    static bool compare(const pair<string, int>&a, const pair<string, int>&b);

public:
    Knn(string metric, int k, vector<DataBase::object> db);
    void updateK(int k);
    void updateDistanceMetric(string distanceMetric);
    string predict(vector<double> x);
    DistanceMetric metric;
    int k;
    string distanceMetric;
};
#endif //AP1_KNN_H
