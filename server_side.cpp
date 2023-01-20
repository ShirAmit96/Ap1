#include "server_side.h"
#include "socketIO.h"
#include "cli.h"


bool Server::extractFromBuffer(char* buffer, vector<double> &vec, int &k, string &distanceMetric) {
    vector<string> firstVec= separateByAlpha(buffer);
    vector<string> secondVec= separateString(firstVec[1]," ");
    k=checkPositiveInt(secondVec[1]);
    string metric=secondVec[0];
    distanceMetric.assign(metric);
    vec= createNumbersVec(firstVec[0]);
    if(k==0||vec.size()==0||!checkMetric(metric)){
        return false;
    }
    return true;
}

int Server::initServer(char **argv) {
    // check if port is available
    int serverPort = validPort(argv[1]);
    if (serverPort == 0) {
        cout << "Server: invalid port. exiting..." << endl;
        exit(-1);
    }
    cout << serverPort<< endl;
    // AF_INET - defines working on Ipv4
    // SOCK_STREAM- DEFINES TCP
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    // if an error occurred while creating the socket-a negative number will be returned:
    if (server_sock < 0) {
        cout << "error creating socket" << endl;
        exit(-1);
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
    sin.sin_port = htons(serverPort);
    // connect the socket to the data that is in the struct:
    if (bind(server_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error binding socket" << endl;
    }
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        // create a new socket for the client using accept command:
        int client_sock = -1;
        cout << client_sock << endl;
        while(client_sock == -1) {
            client_sock = accept(server_sock, (struct sockaddr *) &client_sin ,&addr_len);
        }
        cout << client_sock << endl;
        // check if the creation of the socket for the client failed:
        if (client_sock < 0) {
            cout << "error accepting client" << endl;
        } else {
            return client_sock;
        }
        return server_sock;

}

int Server::createClientSocket(int server_sock) {
        // create an address struct for the client:
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        // create a new socket for the client using accept command:
        int client_sock = -1;
        while(client_sock == -1) {
            client_sock = accept(server_sock, (struct sockaddr *) &client_sin ,&addr_len);
        }
        cout << client_sock << endl;
        // check if the creation of the socket for the client failed:
        if (client_sock < 0) {
            cout << "error accepting client" << endl;
        } else {
            return client_sock;
        }

}
void Server::handleClient(int clientId){
    DefaultIO* sio  = new SocketIO(clientId);
    cout<<"line 73"<< endl;
    Cli cli(sio);
    cout<<"line 75"<<endl;
    cli.start();
    cout<<"line 77"<<endl;
}

int Server::run(char** argv){
    // check if port is available
    int serverPort = validPort(argv[1]);
    if(serverPort==0){
        cout<<"Server: invalid port. exiting..."<<endl;
        exit(-1);
    }

    // AF_INET - defines working on Ipv4
    //SOCK_STREAM- DEFINES TCP
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    // if an error occurred while creating the socket-a negative number will be returned:
    if (server_sock < 0) {
        cout<<"error creating socket"<<endl;
        exit(-1);
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
    sin.sin_port = htons(serverPort);
    // connect the socket to the data that is in the struct:
    if (bind(server_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout<<"error binding socket"<<endl;
    }
    //listen command tells the server to wait for a message from the client.
    // "1" is the max number of clients
    if (listen(server_sock, 1) < 0) {
        cout<<"error listening to a socket"<<endl;
    }
    while(true) {
        // create an address struct for the client:
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        // create a new socket for the client using accept command:
        int client_sock = accept(server_sock, (struct sockaddr *) &client_sin,&addr_len);
        cout << client_sock<< endl;
        // check if the creation of the socket for the client failed:
        if (client_sock < 0) {
            cout<<"error accepting client"<<endl;
        }
        else{
            cout << client_sock<< endl;
            return client_sock;
        }

        while (true) {
            char buffer[4096];
            // define the maximum length of data to receive:
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
            if (expected_data_len<read_bytes){
                break;
            }
            if (read_bytes == 0) {
                break;
            } else if (read_bytes < 0) {
                break;
            }
        }

    }
    close(server_sock);
    return 1;
}

int main(int argc, char* argv[]){
    Server server;
    int client_sock = server.run(argv);
    //int serverSock = server.initServer(argv);
    //cout << serverSock << endl;
    //int clientSock = server.createClientSocket(serverSock);
    cout << client_sock << endl;
    server.handleClient(client_sock);
    //server.run(argv);
    return 0;
}
