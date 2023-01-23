#include "socketIO.h"


string SocketIO::read() {
    char * buffer = new char[4096];
    memset(buffer,0,4096);
    int read_bytes = recv(sock, buffer, 4096, 0);
    if(read_bytes < 0){
        return "Server: error reading from socket, goodbye!";
    }
    buffer[read_bytes] = '\0';
    string output = string(buffer);
    cout << "in socketio read: " << output << endl;
    delete[] buffer;
    return output;
}

void SocketIO::write(string message){
    const char* msg=message.c_str();
    send(sock,msg,message.length(),0);
}
