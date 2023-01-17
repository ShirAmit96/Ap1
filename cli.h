//
// Created by 97252 on 14/01/2023.
//

#ifndef AP1_CLI_H
#define AP1_CLI_H
#include <vector>
#include <algorithm>
#include <string.h>
#include "command.h"
#include "uploadCSV.h"
#include "settings.h"
#include "display_results.h"
#include "classify.h"
#include "download.h"
#include "exit.h"
using namespace std;


class Cli {
    vector<Command*> commands;
    DefaultIO* dio;
public:
    Cli(DefaultIO* dio);
    void start();
    virtual ~Cli();
};


#endif //AP1_CLI_H
