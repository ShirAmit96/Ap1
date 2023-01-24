//
// Created by 97252 on 11/01/2023.
//

#ifndef AP1_SOCKETIO_H
#define AP1_SOCKETIO_H
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include "defaultIO.h"
/*This class inherits the abstract class Defaults IO.
 *it implements read and write functions using sockets*/
class SocketIO:public DefaultIO {
    int sock;
public:

    SocketIO(int sock):sock(sock){}
    virtual string read();
    virtual void write(string text);
};


#endif //AP1_SOCKETIO_H
