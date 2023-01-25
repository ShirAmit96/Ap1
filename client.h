//
// Created by leibguy on 28/12/2022.
//

#ifndef AP1_CLIENT_H
#define AP1_CLIENT_H
#include "input_validation.h"
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <thread>
#include "defaultIO.h"
#include "socketIO.h"
class Client{
    DefaultIO* sio;
public:
    void run(int argc, char** argv);
    string receiveFromServer(int sock);
    void sendToServer(int sock, string message);
    void handleCmd1(int sock);
    void handleCmd2(int sock, string message);
    void handleCmd5(int sock);
    void writeResults(string results, string filePath);
};
#endif //AP1_CLIENT_H
