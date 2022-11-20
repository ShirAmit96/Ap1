#include <cmath>
#include <iostream>
using namespace std;

float general_dist_func(float vector1[], float vector2[],int array_size, int p){
    int x = 0;
    // add a for loop that adds zero to the smaller array in case of not equal len. 
    //int len = min(sizeof(vector1),sizeof(vector2));
    for (int i = 0 ; i<array_size;i++){
        x += ((vector1[i]-vector2[i])  );
    }
    return pow(pow(x,p),(1/p));
}