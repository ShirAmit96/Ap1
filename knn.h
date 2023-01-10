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
    Knn(bool initialized = false,string metric_input = "", int k = 0,
             vector<DataBase::object> db = vector<DataBase::object>());
    Knn(string metric, int k, vector<DataBase::object> db);
    void updateK(int k);
    void updateDistanceMetric(string distanceMetric);
    DataBase predict(DataBase &unclassified_db);
    DistanceMetric metric;
    int k;
    string distanceMetric;
    bool initialized_;
};
#endif //AP1_KNN_H
