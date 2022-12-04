#include <functional>
#include "header.h"
#include "iostream"
using namespace std;
class DistanceMetric{
private:
    string metric;
public:
    DistanceMetric(string distanceMetric) {
        metric = distanceMetric;
    };
    double calculate(vector<double> x, vector<double> y){
        if (metric == "AUC") {
            return DistanceMetric::euclideanDistance(x,y);
        }
        if (metric == "MAN") {
            return DistanceMetric::manhattanDistance(x,y);
        }
        if (metric == "CHB") {
            return DistanceMetric::chebyshevDistance(x,y);
        }
        if (metric == "CAN") {
            return DistanceMetric::canberraDistance(x,y);
        }
        if (metric == "MIN") {
            return DistanceMetric::minkowskyDistance(x,y);
        }
    };
    /*This function is a generalized compute distance function and it'll
    compute different distance depends on the p value that is passed -
    if p=1 is the distance is manhattan, if p=2 the distance is euclidean and for all the other p values the distance is minkowsky*/
    double generalDistFunc(vector<double> x, vector<double> y, double p)
    {
        double z = 0;
        for (int i = 0; i < x.size(); i++)
        {
            z += pow((abs(x[i] - y[i])), p);
        }
        return pow(z, (1.0 / p));
    }
    /*This function gets two vectors of double and returns the euclidean distance between them*/
    double euclideanDistance(vector<double> x, vector<double> y)
    {
        return generalDistFunc(x, y, 2);
    }
    /*This function gets two vectors of double and returns the manhattan distance between them*/
    double manhattanDistance(vector<double> x, vector<double> y)
    {
        return generalDistFunc(x, y, 1);
    }
    /*This function gets two vectors of double and returns the minikowsky distance between them*/
    double minkowskyDistance(vector<double> x, vector<double> y)
    {
        return generalDistFunc(x, y, 3);
    }
    /*This function gets two vectors of double and returns the chebyshev distance between them*/
    double chebyshevDistance(vector<double> x, vector<double> y)
    {
        double max = 0;
        double subAbs = 0;
        for (int i = 0; i < x.size(); ++i)
        /* for each value in the same index in the two vectors
        compute the absolute value of their subtraction and find the maximum between all*/
        {
            subAbs = abs(x[i] - y[i]);
            if (i == 0)
            {
                max = subAbs;
            }
            else if (subAbs > max)
            {
                max = subAbs;
            }
        }
        return max;
    }
    /*This function gets two vectors of double and returns the canberra distance between them*/
    double canberraDistance(vector<double> x, vector<double> y)
    {
        double subAbs = 0;
        double sumAbs = 0;
        double sigma = 0;
        for (int i = 0; i < x.size(); ++i)
        {
            /*Compute the abslute value of each value
            and then subtract the values that are in the same index in the two vectors*/
            subAbs = abs(x[i] - y[i]);
            /*Compute the abslute value of each value
            and then sum the values that are in the same index in the two vectors*/
            sumAbs = abs(x[i]) + abs(y[i]);
            /*If it's not a case of division by zero :add to the sigma variable the divison of the subtraction by the sum*/
            if (sumAbs != 0)
            {
                sigma += (subAbs / sumAbs);
            }
        }
        return sigma;
    }
};

