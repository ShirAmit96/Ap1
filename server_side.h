//
// Created by leibguy on 31/12/2022.
//

#ifndef AP1_SERVER_SIDE_H
#define AP1_SERVER_SIDE_H
#include "knn.h"
#include "reader_class.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>

using namespace std;
class Server {
public:
    int setup(char** argv);
    int createClientSocket(int serverSock) ;
    void extractFromBuffer(char* buffer, vector<double>& vec, int& k,string& distanceMetric);
    void sendToClient(const char* data, int length, int clientSock);
    void recieve(int clientSock);
    void close();
    DataBase global_db;
    Knn k_model;

private:
    int serverSocket;
    int clientSocket;
};

#endif //AP1_SERVER_SIDE_H
