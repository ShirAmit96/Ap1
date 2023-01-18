
#ifndef AP1_DEFAULTIO_H
#define AP1_DEFAULTIO_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual ~DefaultIO(){}
};


#endif //AP1_DEFAULTIO_H
