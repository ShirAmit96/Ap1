#include "socketIO.h"


string SocketIO::read(){
    char c=0;
    string s="";
    while(c!='\n'){
        recv(sock,&c,sizeof(char),0);
        s+=c;
    }
    return s;
}
void SocketIO::write(string message){
    const char* msg=message.c_str();
    send(sock,msg,strlen(msg),0);
}