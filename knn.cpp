#include "knn.h"
//default constructor
Knn::Knn(bool initialized, string metric_input, int k,vector<DataBase::object> db)
: metric(metric_input), db(db), initialized_(initialized) {
    this->distanceMetric = metric_input;
    this->k = k;
}

// the Knn constructor.
Knn::Knn(string metric_input, int k, vector<DataBase::object> db)
: metric(metric_input), db(db), initialized_(true) {
    this->distanceMetric = metric_input;
    this->k = k;
}
// compute the distance between the given vectors to all the vectors in the database.
vector<pair<double,string>> Knn::distance(vector<DataBase::object> database, vector<double> x){
    vector<pair<double,string>> distancesAndLabels={};
    double distance = 0;
    string label = "";
    for(int i =0;i<database.size();i++){
        distance=(this->metric.calculate(database[i].values,x));
        label = database[i].label;
        //pushing to the vector distance between unknown vector and a vector from the database
        //with the corresponding label.
        distancesAndLabels.push_back(make_pair(distance,label));
    }
    //sort the vector by the distance in ascending order.
    sort(distancesAndLabels.begin(),distancesAndLabels.end());
    return distancesAndLabels;
}
    //create a vector with the labels of the k nearest neighbors.
    vector<string> Knn::nearestKNeighbors(vector<pair<double,string> > distancesAndLabels, int k){
        vector<string> labels = {};
        for(int i = 0; i<k;i++){
            labels.push_back(distancesAndLabels[i].second);
        }
        return labels;
    }
    //helper method to compare between two values in a map.
    bool Knn::compare(const pair<string, int>&topLabel, const pair<string, int>&bottomLabel)
    {
        return topLabel.second<bottomLabel.second;
    }
    //This method create a map-> label:occurrences.
    //After that the method finds the max element using the compare method.
    string Knn::mostCommonLabel(const vector<string> &labels){
        map<string,unsigned long> labels_count;
        for (const auto &label : labels)
            ++labels_count[label];
        return max_element(labels_count.cbegin(), labels_count.cend(), compare)->first;
}
    // The predict method calls all the necessary functions in order to make a prediction.
    // First compute distance from unknown vector from the unclassified database to all vectors in database.
    // Then find the labels of the k nearest neighbors.
    // At the end find and return the most common label.
    DataBase Knn::predict(DataBase &unclassified_db){
        for(auto vec:unclassified_db.db) {
            vector<pair<double, string>> distancesAndLabels = distance(this->db, vec.values);
            vector<string> labels = nearestKNeighbors(distancesAndLabels, this->k);
            string label = mostCommonLabel(labels);
            vec.label = label;
        }
        return unclassified_db;
    }

void Knn::updateK(int k) {
    this->k = k;
}

void Knn::updateDistanceMetric(string distanceMetric){
        this->metric.metric = distanceMetric;
        this->distanceMetric = distanceMetric;
}

