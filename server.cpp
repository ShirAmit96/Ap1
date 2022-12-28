//
// Created by 97252 on 28/12/2022.
//
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
using namespace std;
#include "server.h"
int main() {
    //The port comes from the user:
    const int server_port = 5555;
    // AF_INET - defines working on Ipv4
    //SOCK_STREAM- DEFINES TCP
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    // if an error occurred while creating the socket-a negative number will be returned:
    if (server_sock < 0) {
        perror("error creating socket");
    }
    // struct for address.
    struct sockaddr_in sin;
    //reset the struct
    memset(&sin, 0, sizeof(sin));
    //address protocol type
    sin.sin_family = AF_INET;
    //const for any address
    sin.sin_addr.s_addr = INADDR_ANY;
    //convert port's number from how it represented in our computer memory to how the network going to present it:
    sin.sin_port = htons(server_port);
    // connect the socket to the data that is in the struct:
    if (bind(server_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    //listen command tells the server to wait for a message from the client.
    // "1" is the max number of clients
    if (listen(server_sock, 1) < 0) {
        perror("error listening to a socket");
    }
    // create an address struct for the client:
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    // create a new socket for the client using accept command:
    int client_sock = accept(server_sock, (struct sockaddr *) &client_sin, &addr_len);
    // check if the creation of the socket for the client faild:
    if (client_sock < 0) {
        perror("error accepting client");
    }
    char buffer[4096];
    // define the maximum length of data to receive:
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    //send buffer to input validation check
    //send buffer to knn

    //send beffer
    if (read_bytes == 0) {
    // connection is closed
    } else if (read_bytes < 0) {
    //error
    } else {
        //got a message from client
        cout << buffer;
    }
    // put the result of knn in send bytes buffer
    int sent_bytes = send(client_sock, buffer, read_bytes, 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
    close(server_sock);
    return 1;
}