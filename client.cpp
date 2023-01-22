#include "client.h"

int main(int argc, char* argv[]){
    //create client class:
    Client client;
    //run client:
    client.run(argc, argv);
    return 1;
}
using namespace std;

string Client::receiveFromServer(int sock) {
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    //receive the response of the server:
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    //Check if an error occurred while receiving from the server:
    if (read_bytes == 0) {
        //If the server is closed-print a message and close the client:
        cout << "Error connecting to server" << endl;
        close(sock);
        exit(-1);
    } else if (read_bytes < 0) {
        //If an error occurred-print a message and close the client:
        cout << "Error connecting to server" << endl;
        close(sock);
        exit(-1);
    } else {
        string received (buffer);
        return received;
    }
}
void Client::sendToServer(int sock, string message){
    int sent_bytes = send(sock, message.c_str(),message.length()+1, 0);
    //Check if an error occurred while sending to the server:
    if (sent_bytes < 0) {
        //If an error occurred-print a message and close the client:
        cout<<"Error sending to server"<<endl;
        close(sock);
        exit(-1);
    }
}
void Client::handleCmd1(int sock){
    cout<<"Please upload your local train CSV file."<<endl;
    //get path for train file from the user:
    string trainPath;
    getline(cin, trainPath);
    cout << "line 48:" << trainPath << endl;
    //♥ add a condition if the path is not valid
    // read the file and convert it into string:
    ifstream trainStream(trainPath);
    string trainString ="";
    if(trainStream.is_open())
    {
        // read the file and convert it into string:
        stringstream trainBuffer;
        trainBuffer << trainStream.rdbuf();
        trainString = trainBuffer.str();
    }else
        cout<<"Unable to open the file"<<endl;
    //add a sign for the server that the file is ended:
    trainString+="*EOF";
    //Prepare the data for sending to the server:
    //Send the data to the server:
    sendToServer(sock, trainString);
    // part 2 of command 1:
    string serverUpdate1= receiveFromServer(sock);
    //print update from server:
    cout<<serverUpdate1<<endl;
    if(serverUpdate1.find("invalid")!= string::npos){
        return;
    }
    cout<<"Please upload your local test CSV file."<<endl;
    string testPath;
    getline(cin, testPath);
    ifstream testStream(testPath);
    stringstream testBuffer;
    testBuffer << testStream.rdbuf();
    string testString = testBuffer.str();
    testString+="*EOF";
    //Send the data to the server:
    sendToServer(sock, testString);
    string serverUpdate2= receiveFromServer(sock);
    cout<<serverUpdate2<<endl;

}
void Client::writeCSV(string results, string filePath){
    cout << "line 80" << endl;
    fstream file (filePath, ios::out);
    if (file.is_open()) {
        cout << "results" << endl;
        file<<results;
        file.close();
    } else {
        cout<<"invalid path";
    }
}
void Client::handleCmd5(int sock) {
    cout<<"Please enter a csv path: "<<endl;
    string filePath;
    getline(cin, filePath);
    cout <<filePath << endl;
    string updateServer="*pathInserted";
    sendToServer(sock, updateServer);
    string bufferString;
    while (true) {
        string currentBuffer= receiveFromServer(sock);
        bufferString+=currentBuffer;
        cout << "line 99" << currentBuffer << endl;
        if(currentBuffer.find("#EOF")!= string::npos) {
            vector <string> sepEnd= separateString(bufferString, "#EOF");
            string fileContent=sepEnd[0];
            thread t(&Client::writeCSV, this, fileContent, filePath);
            t.detach();
            break;
        }
        else{
            continue;
        }
    }
}
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
    if(connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout<<"Error connecting to server"<<endl;
        //close(sock);
        //exit(-1);
    }
    cout << "line 148" << endl;
    //in buffer string we will put the messages from server:
    string bufferString="";
    //Run in an infinite loop to allow continuous communication with the server:
    while (true) {
            //'currentBuffer' is used for cases in which the buffer is too long for one iteration:
            string currentBuffer = receiveFromServer(sock);
            bufferString+=currentBuffer;
            //check if message is complete:
            if(currentBuffer.find("*END!")!= string::npos){
                vector<string> sepBuffer= separateString(bufferString,"*");
                bufferString= sepBuffer[0];
                //command #1:
                if(bufferString.find("#cmd1")!= string::npos){
                    handleCmd1(sock);
                    cout << "line 165" << endl;
                    bufferString="";
                }else if(bufferString.find("#cmd5")!= string::npos){
                    handleCmd5(sock);
                    bufferString="";
                }else{
                    vector<string> sepCmd= separateString(bufferString,"*");
                    string command=sepCmd[0];
                    cout<<command;
                    if(command.find("invalid")!= string::npos){
                        continue;
                    }
                    if(command.find("classifying data complete")!= string::npos){
                        cout << "DEBUG HERE::::::" << command << endl;
                        sendToServer(sock, "heyheyheyhey");
                        cout << "line 188" << endl;
                        command ="";
                        continue;
                    }
                    string input;
                    getline(cin, input);
                    cout << "******#####getline:" << input << endl;
                    //input = input + "*";
                    sendToServer(sock, input);
                    input ="";
                    bufferString="";
                }
                }else{
                //the message didn't end yet:
                continue;
            }
            }
    }

