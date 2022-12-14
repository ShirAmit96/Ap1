# Ap1
Manual for ex2: 

Instructions for compiling and runing the code: 

Log in to "planet" server and run the following commands:
1. git clone -b ex2 https://github.com/ShirAmit96/Ap1.git
3. cd Ap1 
4. put "iris_classified.csv", "beans_Classified.csv" and "wine_Classified.csv" inside Ap1 directory.
5. make
6. ./a.out <k> <file_name> <distance_metric>

*** k is a number , file name is one of the above files and distance metric can be: AUC, MAN, CHB, CAN, MIN.

our code includes 7 files: 
1. main.cpp - this is the main file of the program. The main handles the calls of the other functions. first, the main will get the first input via args and later, after validation check of the first input, the second input will be inserted.If everything is valid, a predicted label will be printed.
2. input_managment.cpp - This file contains the functions that arrange the input and the send it to input_validation class.if everything is valid, the input will be returned to the main.
3. input_validation.cpp -This file contains the functions which perform valdiation checks on the inserted data. 
4. distance_metric.cpp -
5. database.cpp-This class represents a database that holds a vector of structs and each struct contains size(=numbers of columns), vector of numbers and a matching label.
6. reader_class.cpp-This class reads a given csv file and creates a database class that holds the file content.
7. knn.cpp-

Insturctions for using the program:

1. After running all the above command you should insert a seires of number sepertaed by space.
2. The program will return the predicted label of the vector using knn algorithem.
3. You can continue inserting numbers and predict more vectors from the same category.

validation rules:
1. The amount of numbers you insert should match the size of the vectors in the requested file.
2. Seperate the inserted numbers by one space only and avoid putting space before the first number and after the last.
3. Make sure that the files names are identical to the names mentioned above.
4. Make sure that the number of columns in the csv files is consistent.
5. Make sure that k is a positive natural number and that it is not bigger than the data size.

Any deviation from the above instructions will result in termination of the program.

