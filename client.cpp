#include "client.h"
int main(int argc, char* argv[]){
    Client client;
    client.run(argc, argv);
    return 1;
}
using namespace std;
void Client::run(int argc, char** argv) {
    //create a vector from args in order to send it to a validation check:

    vector<string> inputVec{};
    for(int i=0;i<argc;i++){
        inputVec.push_back(argv[i]);
    }
    //check if the vector is valid and:
    getFirstInput(inputVec);
    const char* ip_address = argv[1];
    const int port_no = stoi(argv[2]);
    // AF_INET - defines working on Ipv4
    //SOCK_STREAM- DEFINES TCP
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // if an error occurred while creating the socket-a negative number will be returned:
    if (sock < 0) {
        cout<<"error creating socket";
        close(sock);
        exit(-1);


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
        cout<<"Error connecting to server";
        close(sock);
        exit(-1);
    }

    //run in infinite loop - add.
    while (true) {
        //get data from user and preform input check - using args
        string input;
        getline(cin, input);
        //check if the user wants to terminate program:
        if(input[0]=='-'&&input[1]=='1'&&input.length()==2){
            cout<<"terminating program..."<<endl;
            close(sock);
            exit(-1);
        }
        if (!checkUserInput(input)){
            cout<<"invalid input"<<endl;
            continue;
        }
        char data_addr[input.length()];
        strcpy(data_addr, input.c_str());
        int data_len = strlen(data_addr);;
        int sent_bytes = send(sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            cout<<"Error sending to server"<<endl;
            close(sock);
            exit(-1);
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout<<"Error connecting to server"<<endl;
            close(sock);
            exit(-1);
        } else if (read_bytes < 0) {
            cout<<"Error connecting to server"<<endl;
            close(sock);
            exit(-1);

        } else {
                cout<<buffer<<endl;
                memset(buffer, 0,sizeof(buffer));
            }

        }

    }

