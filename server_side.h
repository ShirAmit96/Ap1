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
#include "input_validation.h"

using namespace std;
class Server {
public:


    int run(char** argv);
    int initServer(char** argv);
    bool extractFromBuffer(char* buffer, vector<double>& vec, int &k,string& distanceMetric);
    void handleClient(int clientId);
    int createClientSocket(int server_sock);
    Knn k_model;

};

#endif //AP1_SERVER_SIDE_H
