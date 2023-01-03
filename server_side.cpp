#include "server_side.h"

void Server::extractFromBuffer(char* buffer, vector<double> &vec, int &k, string &distanceMetric) {
    // separate the buffer with blank space.
    char* substring = strtok(buffer, " ");
    // while there is a value in the buffer/
    while (substring != nullptr) {
        // checks if it's an alphabetic character.
        if (isalpha(*substring)) {
            distanceMetric.assign(substring);
            // checks if its digit.
        } else if (isdigit(*substring)) {
            vec.push_back(stod(substring));
            // the vector should be inserted before the k.
        } else {
            k = stoi(substring);
        }
        substring = strtok(nullptr, " ");
    }
}
int Server::run(char** argv){
    // check if port is available
    int serverPort;
    cout<<"line 28" << endl;
    try{
        serverPort = stoi(argv[2]);
        if((serverPort<1024)||(serverPort>65535)){
            throw "Server port not available";
        }
    }
    catch(...){
        cout << "Server: invalid port. exiting...";
        return -1;
    }

    // check if file is csv
    cout<<"line 40"<<endl;
    string fileName = argv[1];
    string suffix = ".csv";
    // create the database for the knn.
    ReaderClass read=ReaderClass(fileName);
    DataBase db=read.readCsv();

    // AF_INET - defines working on Ipv4
    //SOCK_STREAM- DEFINES TCP
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    // if an error occurred while creating the socket-a negative number will be returned:
    if (server_sock < 0) {
        perror("error creating socket");
    }
    cout<<"line 55"<<endl;
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
        perror("error binding socket");
    }
    cout<<"line 70"<<endl;
    //listen command tells the server to wait for a message from the client.
    // "1" is the max number of clients
    if (listen(server_sock, 1) < 0) {
        perror("error listening to a socket");
    }
    cout<<"line 76";
        while(true) {
            // create an address struct for the client:
            struct sockaddr_in client_sin;
            unsigned int addr_len = sizeof(client_sin);
            // create a new socket for the client using accept command:
            int client_sock = accept(server_sock, (struct sockaddr *) &client_sin,
                                     reinterpret_cast<socklen_t *>(&addr_len));
            // check if the creation of the socket for the client failed:
            if (client_sock < 0) {
                perror("error accepting client");
                exit(-1);
            }

            while (true) {
                cout << "line 86" << endl;
                char buffer[4096];
                // define the maximum length of data to receive:
                int expected_data_len = sizeof(buffer);
                int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
                cout << read_bytes << endl;

                if (read_bytes == 0) {
                    // connection is closed
                } else if (read_bytes < 0) {
                    //error
                } else {
                    //got a message from client
                    cout << buffer << endl;
                }
                vector<double> vec;
                int k;
                string distanceMetric;
                extractFromBuffer(buffer, vec, k, distanceMetric);
                if (k > db.db.size()) {
                    cout << "Error: k value is bigger than data's size, exiting program..." << endl;
                    exit(-1);
                }
                // This case will be in case the knn model was never initialize with real values- first approach.
                if (k_model.initialized_ == false) {
                    k_model = Knn(distanceMetric, k, db.db);
                    k_model.initialized_ = true;
                }
                if (k_model.initialized_ == true) {
                    if (k_model.distanceMetric != distanceMetric) {
                        k_model.updateDistanceMetric(distanceMetric);
                    }
                    if (k_model.k != k) {
                        k_model.updateK(k);
                    }
                }
                cout << "line 118" << endl;
                cout << k_model.k << endl;
                string label = k_model.predict(vec);
                cout << label << endl;
                cout << "line121" << endl;
                const char *resultBuffer = label.c_str();
                char *copyBuffer = new char[strlen(resultBuffer) + 1];
                strcpy(copyBuffer, resultBuffer);
                int length = label.length();

                // check if need to put here length.
                int sent_bytes = send(client_sock, copyBuffer, length, 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                }
            }
        }
    close(server_sock);
    return 1;

}

int main(int argc, char* argv[]){
    cout << "line 4" << endl;
    cout << "try" << endl;
    Server server;
    cout << "try 2" << endl;
    server.run(argv);
    cout << "try3" << endl;
    return 0;
}
