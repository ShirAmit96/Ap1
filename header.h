#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

using namespace std;
using namespace std;
double generalDistFunc(vector<double> x, vector<double> y, double p);
double euclideanDistance(vector<double> x, vector<double> y);
double manhattanDistance(vector<double> x, vector<double> y);
double minkowskyDistance(vector<double> x, vector<double> y);
double chebyshevDistance(vector<double> x, vector<double> y);
double canberraDistance(vector<double> x, vector<double> y);
vector<string> seperateString(string input);
vector<double> numsCheck(vector<string> xVector);
bool vectorsCheck(vector<double> x, vector<double> y);
vector<double> getInput();
void printDouble(double num);
class InputCheck();
