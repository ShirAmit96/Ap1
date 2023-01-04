# Ap1
Manual for ex3: 

Instructions for compiling and runing the code: 

Log in to "planet" server and run the following commands:
1. git clone -b ex3 https://github.com/ShirAmit96/Ap1.git
3. cd Ap1 
4. make
5. open two terminals- one for the server and one for the client.
6. in the first terminal run the command: ./server.out file port
7. in the second terminal run the command: ./client.out ip port


our code includes 7 files: 
1. client.cpp - This file contains a client class. The client connects a server using an inserted ip and port. After connectong the server it gets from the user a number's vector,distance metric and k .If everything is valid, a predicted label(sended from the server) will be printed.
2. server_side.cpp - this file contains a server class. The server gets as input port number and a path to a file. The server create a database from the file in the path file and a socket with the port number. The server also creates the client socket and connect to the client. The server is waiting for an input from the client, and if the input is valid, the server classify the client's input using the Knn algorithm we implemented in the previous exercise. After calssifing the server sends the label to the client and waits for antoher input. If the input is not valid the server sends a "invalid input" message to the client.
3. input_validation.cpp -This file contains the functions which perform valdiation checks on the inserted data. 
4. distance_metric.cpp - This class represent a distance metric object, the object can calculate distance between two vectors in 5 different distance metrics: Eucldiean, Manhattan, Minkowsky, Chevyshev and Canberra. The choosen metric is given by the an abbreviation given by the user.
5. database.cpp-This class represents a database that holds a vector of structs and each struct contains size(=numbers of columns), vector of numbers and a matching label.
6. reader_class.cpp-This class reads a given csv file and creates a database class that holds the file content.
7. knn.cpp - This class implements the K Nearest Neighbors algorithm. When the predict method is called, first distances between given vector to all the vectors in the databse are computed by the distnace metric according to the metric given by the user. After that the labels of the K nearest neighbors are saved to a vector, and in the end we return the most common label in the vector as the predicted label to the given vector.

Insturctions for using the program:

1. After running all the above command you should insert to the client's terminal a seires of numbers, distance metric name( AUC/MAN/CHB/CAN/MIN) and a k value.
2. The predicted label of the vector will be printed.
3. You can continue inserting input(as mentions in 1) and predict more vectors from the same category.
4. If you want to terminate the client's session, insert "-1" in the terminal.
   The server will continue running and will wait for another client.

validation rules:

1. The amount of numbers you insert should match the size of the vectors in the requested file.
2. Seperate the inserted numbers by one space only and avoid putting space before the first number and after the last.
3. Make sure that the files names are identical to the names mentioned above.
4. Make sure that the number of columns in the csv files is consistent.
5. Make sure that k is a positive natural number and that it is not bigger than the data size.
6. Make sure the port is a number between 1024-65535.
7. Make sure that the inserted ip is valid.

Any deviation from the above instructions client  will result in termination of the program.

