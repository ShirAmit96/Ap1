//
// Created by 97252 on 11/01/2023.
//

#ifndef AP1_SOCKETIO_H
#define AP1_SOCKETIO_H
#include <vector>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;


class DefaultIO {
public:
    virtual string read() const = 0;
    virtual void write(string input) = 0;
};

/**
 * class for standard input/output.
 */
class StandardIO : public DefaultIO {
public:
    string read() const {
        string input;
        getline(cin, input);
        return input;
    };

    void write(string input) {
        cout << input << endl;
    }
};

class SocketIO : public DefaultIO {
    int sock;
public:
    SocketIO(int sock) { this->sock = sock; }

    string read() const {
                vector<char> messageVec;
                // an array to save the bytes of the sended message:
                char bytesArray[sizeof(unsigned int)];
                // read the length of the message
                recv(sock, bytesArray, sizeof(unsigned int), 0);
                // extract the wanted data size:
                int dataSize = *(unsigned int *)bytesArray;
                // resize the vector to the expected size:
                messageVec.resize(dataSize);
                // receive the message from the client:
                int countBytes= 0;
                //this var is pointer to the location in the buffer where the next chunk should be stored:
                char *locPointer = messageVec.data();
                //reads the message from the client in chunks:
                while (countBytes <dataSize) {
                    int currBytes = recv(sock, locPointer, dataSize - countBytes, 0);
                    if (currBytes <= 0) {
                        return "";
                    }
                    countBytes += currBytes;
                    // increments the buffer position pointer by the number of bytes read:
                    locPointer+=  currBytes;
                }
                string output(messageVec.begin(), messageVec.end());
                size_t finalPos = output.find("@@");
                string finalOutput = output.substr(0,finalPos);
                return finalOutput;
    };



    void write(string input) {
            int messageLen = input.length() + 1;
            // create an array to store the bytes of the message length
            char lenBytes[sizeof(unsigned int)];
            // convert the message length to bytes
            memcpy(lenBytes, &messageLen, sizeof(unsigned int));
            // send the size of the message:
            send(sock, lenBytes, sizeof(unsigned int), 0);
            // send the message:
            send(sock, input.c_str(), messageLen, 0);
        }

    };


#endif //AP1_SOCKETIO_H
