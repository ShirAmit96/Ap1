#include "knn.h"

 vector<double> Knn::distance(vector<vector<double>> database, vector<double> x){
    vector<double> distances;
    for(int i =0;i<database.size();i++){
        distances.push_back(this->metric->calculate(database[i],x));
    }
    return distances;
}
 // vector<string> nearestKNeighbors(){}
  //string mostCommonLabel(){}
    Knn::Knn(string metric_input, int k)
    : metric(nullptr){
        this->distanceMetric=metric_input;
        this->k = k;
        metric = new DistanceMetric(this->distanceMetric);
    }
    string Knn::predict(vector<vector<double>> database, vector<double> x){
    distance(database,x);
    }