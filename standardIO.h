#ifndef AP1_STANDARDIO_H
#define AP1_STANDARDIO_H
#include "defaultIO.h"
#include <iostream>
#include <string>
using namespace std;

class StandardIO:public DefaultIO{
public:

    virtual string read();
    virtual void write(string text);
};


#endif //AP1_STANDARDIO_H
