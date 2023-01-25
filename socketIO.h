#ifndef AP1_SOCKETIO_H
#define AP1_SOCKETIO_H
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>
#include <string.h>
#include <vector>
#include "defaultIO.h"
/*This class inherits the abstract class Defaults IO.
 *it implements read and write functions using sockets*/
class SocketIO:public DefaultIO {
    int sock;

public:
    virtual void write(string text);

    virtual string read();

    SocketIO(int sock) : sock(sock) {}
};

#endif //AP1_SOCKETIO_H
