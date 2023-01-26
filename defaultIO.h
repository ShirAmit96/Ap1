#ifndef AP1_DEFAULTIO_H
#define AP1_DEFAULTIO_H
#include <vector>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;


class DefaultIO {
public:
    virtual string read() const = 0;
    virtual void write(string input) = 0;
};

// A declaration for the SokcetIO class, which will handle the communication through socket.
class SocketIO : public DefaultIO {
    int sock;
public:
    SocketIO(int sock) { this->sock = sock; }
    string read() const;
    void write(string input);

};


#endif //AP1_DEFAULTIO_H
