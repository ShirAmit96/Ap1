
#include "client.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
using namespace std;
int main() {
    // who gives to who
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;
    // AF_INET - defines working on Ipv4
    //SOCK_STREAM- DEFINES TCP
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // if an error occurred while creating the socket-a negative number will be returned:
    if (sock < 0) {
        perror("error creating socket");
    }
    // struct for address.
    struct sockaddr_in sin;
    //reset the struct
    memset(&sin, 0, sizeof(sin));
    //address protocol type
    sin.sin_family = AF_INET;
    //const for any address
    sin.sin_addr.s_addr = inet_addr(ip_address);
    //convert port's number from how it represented in our computer memory to how the network going to present it:
    sin.sin_port = htons(port_no);
    // connect the socket to the data that is in the struct:
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }

    //run in infinite loop - add.
    //get data from user and preform input check - using args
    char data_addr[] = "Im a message";
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
// error
    }
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    // gets the label from the server
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
// connection is closed
    }
    else if (read_bytes < 0) {
// error
    }
    else {
        cout << buffer;
    }
    close(sock);
    return 0;
}