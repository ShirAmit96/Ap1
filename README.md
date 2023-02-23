# Ap1
Manual for ex2: 

Instructions for compiling and runing the code: 

Log in to "planet" server and run the following commands:
1. git clone -b fix_ex2 https://github.com/ShirAmit96/Ap1.git
3. cd Ap1 
4. make
5. ./a.out < k > <file_name> <distance_metric>

*** k is a number , file name is your classified file and distance metric can be: AUC, MAN, CHB, CAN, MIN.

our code includes 7 files: 
1. main.cpp - this is the main file of the program. The main handles the calls of the other functions. first, the main will get the first input via args and later, after validation check of the first input, the second input will be inserted.If everything is valid, a predicted label will be printed.
2. input_managment.cpp - This file contains the functions that arrange the input and the send it to input_validation class.if everything is valid, the input will be returned to the main.
3. input_validation.cpp -This file contains the functions which perform valdiation checks on the inserted data. 
4. distance_metric.cpp - This class represent a distance metric object, the object can calculate distance between two vectors in 5 different distance metrics: Eucldiean, Manhattan, Minkowsky, Chevyshev and Canberra. The choosen metric is given by the an abbreviation given by the user.
  important note: in Minikowsky distance p=3.
5. database.cpp-This class represents a database that holds a vector of structs and each struct contains size(=numbers of columns), vector of numbers and a matching label.
6. reader_class.cpp-This class reads a given csv file and creates a database class that holds the file content.
7. knn.cpp- This class implements the K Nearest Neighbors algorithm. When the predict method is called, first distances between given vector to all the vectors in the databse are computed by the distnace metric according to the metric given by the user. After that the labels of the K nearest neighbors are saved to a vector, and in the end we return the most common label in the vector as the predicted label to the given vector. 


Insturctions for using the program:

1. After running all the above command you should insert a seires of number sepertaed by space.
![image](https://user-images.githubusercontent.com/90501635/207836295-0e3f1fcc-14c3-4eab-a5c9-c881981ccad4.png)

2. The program will return the predicted label of the vector using knn algorithm.
  
![image](https://user-images.githubusercontent.com/90501635/207836336-f5cf731a-fe74-4df3-91df-16e9b85ef765.png)

3. You can continue inserting numbers and predict more vectors from the same category.

validation rules:
1. The amount of numbers you insert should match the size of the vectors in the requested file.
2. Seperate the inserted numbers by one space only and avoid putting space before the first number and after the last.
3. Make sure that the file is a csv file.
4. Make sure that the number of columns in the csv files is consistent.
5. Make sure that k is a positive natural number and that it is not bigger than the data size.

Any deviation from the above instructions will result in termination of the program.

