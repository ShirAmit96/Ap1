#include "socketIO.h"

/*This function reads a message that has been received in the socket and returns it.  */
string SocketIO::read() {
    // read using receive function:
    char * buffer = new char[4096];
    memset(buffer,0,4096);
    int read_bytes = recv(sock, buffer, 4096, 0);
    // if the reception failed - return an error:
    if(read_bytes < 0){
        return "Server: error reading from socket";
    }
    // delete buffer to prevent memory leak:
    buffer[read_bytes] = '\0';
    // return the received string:
    string output = string(buffer);
    delete[] buffer;
    return output;
}
/*This function gets a string and send it using the socket. */
void SocketIO::write(string message){
    //convert the string to a const char*:
    const char* msg=message.c_str();
    // send the message:
    send(sock,msg,message.length(),0);
}
