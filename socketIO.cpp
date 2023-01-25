//#include "socketIO.h"
//
///*This function reads a message that has been received in the socket and returns it.  */
//string SocketIO::read() {
//    // read using receive function:
//    string output ="";
//    while(true) {
//        cout << "SOCKET IO STARTED TO READ" << endl;
//        char *buffer = new char[4096];
//        memset(buffer, 0, 4096);
//        int read_bytes = recv(sock, buffer, 4096, 0);
//        // if the reception failed - return an error:
//        if (read_bytes < 0) {
//            return "Server: error reading from socket";
//        }
//        cout << "Satrt reading the rest" << endl;
//        if(read_bytes<4095){
//            cout << "READ THE REST" << string(buffer)<<endl;
//        }
//        //buffer[read_bytes] = '\0';
//        output += buffer;
//        cout << "From socketio:"<<output<<endl;
//        delete[] buffer;
//        if (output.find("@@")!=string::npos){
//            break;
//        }
//        // delete buffer to prevent memory leak:
//        // return the received string:
//    }
//    size_t finalPos = output.find("@@");
//    string finalOutput = output.substr(0,finalPos);
//    cout << "THE FINAL OUTPUT" << finalOutput << endl;
//    return finalOutput;
//}
//
//
///*This function gets a string and send it using the socket. */
//void SocketIO::write(string str) {
//    cout << "SOCKETIO GOT THIS TO WRITE:::" << str << endl;
//    // if the string is too long, send it in a loop
//    if (str.length() > 4095){
//        int init_index = 0;
//        // send file content in a loop
//        while(true) {
//            // substring to send
//            string part_of_data_to_send =  str.substr(init_index, 4095);
//            // create char array for this part of data
//            char str_to_char_arr[(part_of_data_to_send).length()];
//            // copy the string part to the char array
//            strcpy(str_to_char_arr, part_of_data_to_send.c_str());
//
//            int sent_bytes = send(sock, str_to_char_arr, sizeof(str_to_char_arr), 0);
//            if (sent_bytes < 0) {
//                perror("error sending to client");
//            }
//            // update substring start position
//            init_index += 4095;
//            if (sent_bytes < 4095) {
//                // done sending file content
//                break;
//            }
//        }
//    } else { // send the string
//        char str_to_char_arr[(str).length()];
//        strcpy(str_to_char_arr, str.c_str());
//        cout << "SOCKET IO WROTE THIS::::" << str_to_char_arr<< endl;
//        int sent_bytes = send(sock, str_to_char_arr, sizeof(str_to_char_arr), 0);
//        cout << "SOCKET IO FINISHED SENDING" << endl;
//        if (sent_bytes < 0) {
//            perror("error sending to client");
//        }
//    }
//}
