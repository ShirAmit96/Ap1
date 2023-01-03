#include "server_side.h"


bool Server::extractFromBuffer(char* buffer, vector<double> &vec, int &k, string &distanceMetric) {
    vector<string> firstVec= separateByAlpha(buffer);
    vector<string> secondVec= separateString(firstVec[1]," ");
    k=checkK(secondVec[1]);
    string metric=secondVec[0];
    distanceMetric.assign(metric);
    vec= createNumbersVec(firstVec[0]);
    if(k==0||vec.size()==0||!checkMetric(metric)){
        return false;
    }
    return true;
}
int Server::run(char** argv){
    // check if port is available
    int serverPort = validPort(argv[2]);
    if(serverPort==0){
        cout<<"Server: invalid port. exiting..."<<endl;
        exit(-1);
    }

    // check if file is csv
    string fileName = argv[1];
    if(!validFile(fileName)){
        cout<<"Server: invalid file name"<<endl;
        exit(-1);
    }
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
    //listen command tells the server to wait for a message from the client.
    // "1" is the max number of clients
    if (listen(server_sock, 1) < 0) {
        perror("error listening to a socket");
    }
        while(true) {
            // create an address struct for the client:
            struct sockaddr_in client_sin;
            unsigned int addr_len = sizeof(client_sin);
            // create a new socket for the client using accept command:
            int client_sock = accept(server_sock, (struct sockaddr *) &client_sin,
                                     reinterpret_cast<socklen_t *>(&addr_len));
            // check if the creation of the socket for the client failed:
            if (client_sock < 0) {
                cout<<"error accepting client"<<endl;
            }

            while (true) {
                char buffer[4096];
                // define the maximum length of data to receive:
                int expected_data_len = sizeof(buffer);
                int read_bytes = recv(client_sock, buffer, expected_data_len, 0);

                if (read_bytes == 0) {
                    cout<<"0"<<endl;
                    break;
                } else if (read_bytes < 0) {
                    cout<<"-"<<endl;
                    break;
                } else {
                    //got a message from client
                }
                vector<double> vec;
                int k;
                string distanceMetric;
                bool validInput=extractFromBuffer(buffer, vec, k, distanceMetric);
                int columnsSize=db.db[0].size;
                if(columnsSize!=vec.size()||!validInput||k > db.db.size()){
                    string messageStr="invalid input";
                    char message [messageStr.size() + 1];
                    strcpy(message,messageStr.c_str());
                    int length = strlen(message);
                    int message_sent_bytes = send(client_sock, message, length, 0);
                    if (message_sent_bytes < 0) {
                        //♥
                        perror("error sending to client");
                    }
                    continue;
                }else {
                    // This case will be in case the knn model was never initialize with real values- first approach.
                    if (!k_model.initialized_) {
                        k_model = Knn(distanceMetric, k, db.db);
                        k_model.initialized_ = true;
                    }
                    if (k_model.initialized_) {
                        if (k_model.distanceMetric != distanceMetric) {
                            k_model.updateDistanceMetric(distanceMetric);
                        }
                        if (k_model.k != k) {
                            k_model.updateK(k);
                        }
                    }
                    string label = k_model.predict(vec);
                    char copyBuffer [label.size()];
                    strcpy(copyBuffer, label.c_str());
                    int length = label.length();

                    // check if need to put here length.
                    int sent_bytes = send(client_sock, copyBuffer, length, 0);
                    memset(copyBuffer, 0, length);
                    if (sent_bytes < 0) {
                        //♥
                        perror("error sending to client");
                    }
                }
            }

        }
    close(server_sock);
    return 1;

}

int main(int argc, char* argv[]){
    Server server;
    server.run(argv);
    return 0;
}
