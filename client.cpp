#include "client.h"

int main(int argc, char* argv[]){
    //create client class:
    Client client;
    //run client:
    client.run(argc, argv);
    return 1;
}
using namespace std;
/*This class represents a client that communicates with a server*/
void Client::run(int argc, char** argv) {
    /*This function creates a socket, connects to the server and communicates with it/ */
    //create a vector from args in order to send it to a validation check:
    vector<string> inputVec{};
    for(int i=0;i<argc;i++){
        inputVec.push_back(argv[i]);
    }
    //check if the command line input is valid(the program will be terminated if not):
    checkFirstInput(inputVec);
    //initialize the given port and ip:
    const char* ip_address = argv[1];
    const int port_no = stoi(argv[2]);
    // AF_INET - defines working on Ipv4
    //SOCK_STREAM- Defines TCP:
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // if an error occurred while creating the socket-a negative number will be returned:
    if (sock < 0) {
        cout<<"error creating socket";
        close(sock);
        exit(-1);
    }
    // create a struct for the address:
    struct sockaddr_in sin;
    //reset the struct:
    memset(&sin, 0, sizeof(sin));
    //address protocol type:
    sin.sin_family = AF_INET;
    //const for any address:
    sin.sin_addr.s_addr = inet_addr(ip_address);
    //convert port's number from how it represented in our computer memory to how the network is going to present it:
    sin.sin_port = htons(port_no);
    // connect the socket to the data that is in the struct:
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout<<"Error connecting to server";
        close(sock);
        exit(-1);
    }
    //Run in an infinite loop to allow continuous communication with the server:
    while (true) {
        //get data from user:
        string input;
        getline(cin, input);
        //check string size:
        if(input.size()<3){
            cout<<"invalid input"<<endl;
            continue;
        }
        //check if the user wants to terminate program:
        if(input[0]=='-'&&input[1]=='1'&&input.length()==2){
            cout<<"terminating program..."<<endl;
            close(sock);
            exit(-1);
        }
        //Check if the inserted input is valid:
        if (!checkUserInput(input)){
            cout<<"invalid input"<<endl;
            continue;
        }
        //Prepare the data for sending to the server:
        int data_len = input.size()+1;
        if(data_len>4096){
            cout<<"invalid input"<<endl;
            continue;
        }
        //Send the data to the server:
        int sent_bytes = send(sock, input.c_str(), data_len, 0);
        //Check if an error occurred while sending to the server:
        if (sent_bytes < 0) {
            //If an error occurred-print a message and close the client:
            cout<<"Error sending to server"<<endl;
            close(sock);
            exit(-1);
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        //receive the response of the server:
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        //Check if an error occurred while receiving from the server:
        if (read_bytes == 0) {
            //If the server is closed-print a message and close the client:
            cout<<"Error connecting to server"<<endl;
            close(sock);
            exit(-1);
        } else if (read_bytes < 0) {
            //If an error occurred-print a message and close the client:
            cout<<"Error connecting to server"<<endl;
            close(sock);
            exit(-1);

        } else {
            //If we managed to receive a message from the server - print it:
                cout<<buffer<<endl;
                memset(buffer, 0,sizeof(buffer));
            }
        }
    }

