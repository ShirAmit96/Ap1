#include "knn.h"
// compute the distance between the given vectors to all the vectors in the database.
vector<pair<double,string>> Knn::distance(vector<DataBase::object> database, vector<double> x){
    vector<pair<double,string>> distancesAndLabels={};
    double distance = 0;
    string label = "";
    for(int i =0;i<database.size();i++){
        distance=(this->metric->calculate(database[i].values,x));
        label = database[i].label;
        distancesAndLabels.push_back(make_pair(distance,label));
    }
    //sort the vector by the distance in ascending order.
    sort(distancesAndLabels.begin(),distancesAndLabels.end());
    return distancesAndLabels;
}
    //create a vector with the labels of the k nearest neighbors.
    vector<string> Knn::nearestKNeighbors(vector<pair<double,string>> distancesAndLabels, int k){
        vector<string> labels = {};
        for(int i = 0; i<k;i++){
            labels.push_back(distancesAndLabels[i].second);
        }
        return labels;
    }
    //helper method to compare between two values in a map.
    bool Knn::compare(const pair<string, int>&a, const pair<string, int>&b)
    {
        return a.second<b.second;
    }
    //This method create a map-> label:occurrences.
    //After that the method finds the max element using the compare method.
    string Knn::mostCommonLabel(const vector<string> &labels){
        map<string,unsigned long> labels_count;
        for (const auto &label : labels)
            ++labels_count[label];
        return max_element(labels_count.cbegin(), labels_count.cend(), compare)->first;
}
    // the Knn constructor.
    Knn::Knn(string metric_input, int k, vector<DataBase::object> db)
    : metric(nullptr),db(db){
        this->distanceMetric=metric_input;
        this->k = k;
        metric = new DistanceMetric(this->distanceMetric);
    }
    // The predict method calls all the necessary functions in order to make a prediction.
    string Knn::predict(vector<double> x){
        vector<pair<double,string>> distancesAndLabels=distance(this->db,x);
        vector<string> labels = nearestKNeighbors(distancesAndLabels,this->k);
        string label = mostCommonLabel(labels);
        return label;

    }