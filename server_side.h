//
// Created by leibguy on 31/12/2022.
//

#ifndef AP1_SERVER_SIDE_H
#define AP1_SERVER_SIDE_H
#include "knn.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <thread>
#include "input_validation.h"

using namespace std;
class Server {
public:


    void run(char** argv);
    static void handleClient(int clientId);
    bool extractFromBuffer(char* buffer, vector<double>& vec, int &k,string& distanceMetric);

};

#endif //AP1_SERVER_SIDE_H
