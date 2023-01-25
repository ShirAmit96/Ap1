//
// Created by 97252 on 14/01/2023.
//

#ifndef AP1_CLI_H
#define AP1_CLI_H
#include <vector>
#include <algorithm>
#include <string.h>
#include "command.h"
using namespace std;


class Cli {
    vector<Command*> commands;
    SocketIO* dio;
    int sock;
public:
    Cli(SocketIO* dio, int scoket);
    void start();
    virtual ~Cli();

};
#endif //AP1_CLI_H
