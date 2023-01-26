#include "client.h"

int main(int argc, char* argv[]){
    //create client class:
    Client client;
    //run client:
    client.run(argc, argv);
    return 1;
}
using namespace std;


/*This function handles the receiving process from the server and returns its message.*/
string Client::receiveFromServer(int sock) {
    char buffer[4096];
    memset(buffer, 0, 4096);
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
        //if everything is ok return the message received:
        string received (buffer);
        return received;
    }
}
/*This function handles the sending process to the server.*/
void Client::sendToServer(int sock, string message){
    //send the message to the server:
    message +="@@";
    int sent_bytes = send(sock, message.c_str(),message.length()+1, 0);
    //Check if an error occurred while sending to the server:
    if (sent_bytes < 0) {
        //If an error occurred-print a message and close the client:
        cout<<"Error sending to server"<<endl;
        close(sock);
        exit(-1);
    }
}
/*This function handles cmd1. it gets a local path from the user to a classified file
  and sends the content of the file to the server.
  then, it does the same process for  an unclassified file  .*/
void Client::handleCmd1(int sock){
    cout<<"Please upload your local train CSV file."<<endl;
    //get path for train file from the user:
    string trainPath;
    getline(cin, trainPath);
    // read the file:
    ifstream trainStream(trainPath);
    string trainString ="";
    if(trainStream.is_open())
    {
        //convert the file content into a string:
        stringstream trainBuffer;
        trainBuffer << trainStream.rdbuf();
        trainString = trainBuffer.str() +"@@";
        //add a sign for the server that the file is ended:
        //Send the data to the server:
        sio->write(trainString);
        //sendToServer(sock, trainString);
    }else{
        //if the file path is not valid-print an error:
        cout<<"Unable to open the file"<<endl;
        //send a fail message to the server:
        sio->write("failed@@");
        //sendToServer(sock, "failed");
        return;
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(40));
    //receive from the server an update about uploading:
    string serverUpdate1= sio->read();
    //string serverUpdate1= receiveFromServer(sock);
    //print update from server:
    cout<<serverUpdate1<<flush;
    //return if the server says that the input is invalid:
    if(serverUpdate1.find("invalid")!= string::npos){
        return;
    }
    // part 2 of command 1- getting a local path to an unclassified file:
    cout<<"Please upload your local test CSV file."<<endl;
    string testPath;
    getline(cin, testPath);
    //convert the file content into a string:
    ifstream testStream(testPath);
    if(testStream.is_open()) {
        stringstream testBuffer;
        testBuffer << testStream.rdbuf();
        string testString = testBuffer.str()+"@@";
        //add a sign for the server that the file is ended:
        //Send the content of the file to the server:
        sio->write(testString);
        //sendToServer(sock, testString);
        // get update from the server and print it:
        string serverUpdate2= sio->read();
       //string serverUpdate2= receiveFromServer(sock);
        cout<<serverUpdate2<<flush;
    }else{
        //return if the server says that the input is invalid and send the server a fail message:
        cout<<"Unable to open the file"<<endl;
        sio->write("failed@@");
        //sendToServer(sock, "failed");
        return;
    }

}
/*This function handles cmd2.it prints the command received from the server,
 * gets an input from the user and sends it back to server.*/
void Client::handleCmd2(int sock, string message){
    //separate the message from the flag sub string:
    vector<string> sepMessage=separateString(message,"#");
    string currSettings=sepMessage[0];
    //print current settings:
    cout<<currSettings<<flush;
    // get from the user the new settings:
    string newSettings;
    getline(cin, newSettings);
    //send the new settings to the server:
    sio->write(newSettings);
}
/*This function gets a string and a file path and write the string into the given file.*/
void Client::writeResults(string results, string filePath){
    // try to open the path and enable writing permissions:
    fstream file (filePath, ios::out);
    if (file.is_open()) {
        //write the string content into the file:
        file<<results;
        file.close();
    } else {
        //if the path is not valid -print an error:
        cout<<"invalid input"<<endl;
    }
}
/*This function handles cmd5. it asks for a local path from the user,
  gets from the server the results of classification,
  and writes the results to the given file in a separate thread.*/
void Client::handleCmd5(int sock) {
    //get a local path from the user:
    cout<<"Please enter a csv path: "<<endl;
    string filePath;
    getline(cin, filePath);
    // update the server that a path has been inserted:
    string updateServer="*pathInserted";
    sio->write(updateServer);
    //sendToServer(sock, updateServer);
    string bufferString;
    while (true) {
        //get the results of classification from the server:
        string currentBuffer= sio->read();
        bufferString+=currentBuffer;
        //look for "EOF" in order to stop receiving:
        if(currentBuffer.find("#EOF")!= string::npos) {
            //cut the "EOF" from the string:
            vector <string> sepEnd= separateString(bufferString, "#EOF");
            string fileContent=sepEnd[0];
            //open another thread and write the results to the file in it:
            thread t(&Client::writeResults, this, fileContent, filePath);
            t.detach();
            break;
        }
        else{
            continue;
        }
    }
}
/*This function creates a socket, connects to the server and communicates with it */
void Client::run(int argc, char** argv) {
    //create a vector from args in order to send it to a validation check:
    vector<string> inputVec{};
    for (int i = 0; i < argc; i++) {
        inputVec.push_back(argv[i]);
    }
    //check if the command line input is valid(the program will be terminated if not):
    checkFirstInput(inputVec);
    //initialize the given port and ip:
    const char *ip_address = argv[1];
    const int port_no = stoi(argv[2]);
    // AF_INET - defines working on Ipv4
    //SOCK_STREAM- Defines TCP:
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    this->sio = new SocketIO(sock);
    // if an error occurred while creating the socket-a negative number will be returned:
    if (sock < 0) {
        cout << "error creating socket";
        close(sock);
        exit(-1);
    }
    //create a struct for the address:
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
        cout << "Error connecting to server" << endl;
        //close(sock);
        //exit(-1);
    }
    //in buffer string we will put the messages from server:
    string bufferString = "";
    //Run in an infinite loop to allow continuous communication with the server:
    while (true) {
        //'currentBuffer' is used for cases in which the buffer is too long for one iteration:
        string currentBuffer = "";
        currentBuffer = sio->read();
        bufferString += currentBuffer;
        string separatedCmd = bufferString;
        //clean the buffer:
        bufferString = "";
        //handle command #1:
        if (separatedCmd.find("#cmd1") != string::npos) {
            handleCmd1(sock);
            separatedCmd = "";
            //handle command #5:
        } else if (separatedCmd.find("#cmd5") != string::npos) {
            handleCmd5(sock);
            separatedCmd = "";
            //handle command #2:
        } else if (separatedCmd.find("#cmd2") != string::npos) {
            handleCmd2(sock, separatedCmd);
            separatedCmd = "";
        } else {
            string output = separatedCmd;
            separatedCmd = "";
            //handle commands 3 or 4:
            if (output.find("#cmd3") != string::npos || output.find("#cmd4") != string::npos) {
                //separate the "cmd" sign from the string:
                vector<string> sepCmd = separateString(output, "#");
                output = sepCmd[0];
                //print the output of the server:
                cout << output << flush;
                separatedCmd = "";
                continue;
            }
                // if the message is not the menu, print it and continue receiving:
            else if (output.find("Welcome") == string::npos) {
                cout << output << flush;
                continue;
            }
            // Print menu:
            cout << output << flush;
            // get command number from the user:
            string commandNum;
            getline(cin, commandNum);
            commandNum+="@@";
            // send he command to server:
            sio->write(commandNum);
            //sendToServer(sock,commandNum);
            // check if the user wants to exit:
            if (commandNum == "8@@") {
                exit(-1);
            }
            commandNum = "";
        }

        continue;

    }
}
