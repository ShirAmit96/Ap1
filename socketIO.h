//
// Created by 97252 on 11/01/2023.
//

#ifndef AP1_SOCKETIO_H
#define AP1_SOCKETIO_H

#include <string>
#include <string.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;


class DefaultIO {
public:
    // =0 enforces the child classes to override this function with their own implementation
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

    /**
     * reads bytes from network using TCP protocol. First it receives the number of bytes of incoming message,
     * and than the message itself.
     * @return - a string representation of the message.
     */
    string read() const {
        char messageBuffer[4096]; // creates a buffer to receive the message from the client
        memset(messageBuffer, 0, sizeof(messageBuffer));

        // we want to read the length of the upcoming message
        // recv can only give us an array of bytes, but we want an integer

        // a buffer that will hold the bytes that represent the length of the message
        char lenBuffer[sizeof(unsigned int)]; // 29 --> {29, 0, 0, 0}
        // read the length of the message
        recv(sock, lenBuffer, sizeof(unsigned int), 0); /* maximum length of received data */
        // convert the char* ({29, 0, 0, 0}) to int (29)
        int expected_data_len = *(unsigned int *)lenBuffer;
        cout<<"data length: " <<expected_data_len<<endl;

        // receive the message from the clients socket into 'messageBuffer'
        // Problem: recv can potentially return only part of the message (i.e. less than 'expected')
        // Solution: we will track how many bytes we read so far
        //           and keep reading until we reach our 'expected' number of bytes
        int total_bytes = 0;
        // this is the current position in messageBuffer
        char *bufferPos = messageBuffer;
        while (total_bytes < expected_data_len) {
            cout<< "in while receiving:"<<endl;
            // recv will write bytes starting from bufferPos (which is the address of first uninitialized byte in the buffer)
            int read_bytes = recv(sock, bufferPos, expected_data_len - total_bytes, 0);
            cout<<"read: "<<bufferPos<<endl;
            if (read_bytes <= 0) {
                return "";
            }
            // track the number of bytes we read so far
            total_bytes += read_bytes;
            // 'jump over' the bytes that recv wrote, i.e. point to the first uninitialized byte
            bufferPos += read_bytes;
        }
        string output = messageBuffer;
        cout<<"Output: "<<output<<endl;
        size_t finalPos = output.find("@@");
        string finalOutput = output.substr(0,finalPos);
        cout << "THE FINAL OUTPUT" << finalOutput << endl;

        return finalOutput;
    };


    /**
     * sends bytes over network, using TCP protocol. First we send the length of the message, and after we send the
     * actual message which is now expected to be of that length
     * @param input - input string we wish to send
     */
    void write(string input) {
        // we add +1 because of '\0' (null-terminator)
        unsigned int sizeOfMessage = input.size() + 1;
        // we treat the integer as an array of bytes, because 'send' expects array of bytes (chars) while 'size' is int
        char *sizeBytes = (char *)&sizeOfMessage;
        // send the length of the message to "prepare" server for what's coming
        send(sock, sizeBytes, sizeof(unsigned int), 0);
        cout<<"Message 1 sended:"<< sizeof(unsigned int)<<endl;
        // send the actual message (of that length)
        send(sock, input.c_str(), sizeOfMessage, 0);
        cout<<"Message 2 sended:"<< input<<endl;

    };
};

#endif //AP1_SOCKETIO_H
