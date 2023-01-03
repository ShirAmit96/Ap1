//
// Created by leibguy on 28/12/2022.
//

#ifndef AP1_CLIENT_H
#define AP1_CLIENT_H
#include "input_managment.h"
#include "input_validation.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
class Client{
public:
    void run(int argc, char** argv);

};
#endif //AP1_CLIENT_H
