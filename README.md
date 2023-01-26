# Ap1
Manual for ex4: 

Instructions for compiling and runing the code: 

Log in to "planet" server and run the following commands:
1. git clone -b ex4 https://github.com/ShirAmit96/Ap1.git
3. cd Ap1 
4. make
5. open two terminals- one for the server and one for the client.(or more terminals for other clients)
6. in the first terminal run the command: ./server.out <port>
7. in the others  terminals run the command: ./client.out <ip> <port>


our code includes 10 files: 
1. client.cpp - This file contains a client class. The client connects a server using an inserted ip and port. The client prints the information from the server and sends updates from the user to server using "socketIo" class.
2. server_side.cpp - this file contains a server class. The server gets as input port number. The server also creates the client socket and connect to the client using the CLI component and it is waiting for an input from the client. If the input is valid, the server performs the commands the client requested and send the client the output using "socketIO" class. If the input from the client is not valid the server sends a "invalid input" message to the client.
3. input_validation.cpp -This file contains the functions which perform valdiation checks on the inserted data. 
4. distance_metric.cpp - This class represent a distance metric object, the object can calculate distance between two vectors in 5 different distance metrics: Eucldiean, Manhattan, Minkowsky, Chevyshev and Canberra. The choosen metric is given by the an abbreviation given by the user.
5. database.cpp-This class represents a database that holds a vector of structs and each struct contains size(=numbers of columns), vector of numbers and a matching label.
6. reader_class.cpp-This class reads a given csv file and creates a database class that holds the file content.
7. knn.cpp - This class implements the K Nearest Neighbors algorithm. When the predict method is called, first distances between given vector to all the vectors in the databse are computed by the distnace metric according to the metric given by the user. After that the labels of the K nearest neighbors are saved to a vector, and in the end we return the most common label in the vector as the predicted label to the given vector.
8. command.cpp - This class implements the 6 commands the user can do: Upload CSV, see and change the KNN settings, classify the data, display the classification reaults, write the results to a file and exit the program.
9. SocketIO.cpp - This class inherit from DeafaultIO and is incharge of sending and recieving messages through sockets. Both the server and the client use socketIO to communicte with eachother. 
10. cli.cpp - This class is responsible to send the menu to the user, recieved throgh the socket the user input and execute the relvant command.

Insturctions for using the program:

1. After running all the above command on the client side the menu will be printed.
![image](https://user-images.githubusercontent.com/92683819/214888740-b8b416d9-50f2-4726-9e68-bae5b84e435d.png)

3. Now the client can choose which command he wants, and a message will be printed accordingly. 

validation rules:

1. in menu: make sure that you choose number from the following options:1,2,3,4,5,8 and then press enter.
2. in command 1: Make sure that the number of columns in the csv files is consistent.
3. in command 1: Make sure the path to files is valid and that the train and test files are corresponding.
4. in command 2: Seperate the inserted k and metric by one space only and avoid putting space before the first number and after the last.
5. in command 2: make sure you insert only 2 parametrs.
6. in command 2: Make sure that k is a positive natural number and that it is not bigger than the data size.
7. in command 2: Make sure that the distance metric name is AUC/MAN/CHB/CAN/MIN.
8. Make sure the port is a number between 1024-65535.
9. Make sure that the inserted ip is valid.
10. Make sure that the client and server have the same port.

Any deviation from the above instructions will result in error message or termination of the program.

