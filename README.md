# Ap1
Manual for the second part of ex1: 

Instructions for compiling and runing the code:
Log in to "planet" server and write the following commands:
1. git init
2. git clone https://github.com/ShirAmit96/Ap1.git
3. cd Ap1 
4. g++ header.h
5. g++ -std-c++ *.cpp
6. ./a/out

our code include 4 files: 
1. main.cpp - this is the main file of the program. The main handles the calls of the other functions. In the main we create a vectors that will be filled by the user through other function, and later the vectors (if valids) passed to the different distance functions and the returned results printed through the functions in the file output_functions.cpp.
2. input functions.cpp - this file contain the functions that make sure that the user insert valid vectors. The functions inside the file make sure that the vectors are the same size, not empty and don't include any special symbols.
3. distance_functions.cpp - This file contain the methods that compute euclidean, manhattan, chevyshev, canberra and minkowsky distances. 
4. ouput_function.cpp - this file contain a function that takes care of the decimal precision of the output - makes sure that 4 is printed as 4.0. 

Insturctions for using the program:

You will be requested to insert input(twice).
each time you should enter a seires of number sepertaed by space(one or more).
A valid input is a any 2 seires of numbers(negative/positive/with decimal point) and the two seires should be in the same length and not empty.
If the input won't be valid, the program will be terminated.

![image](https://user-images.githubusercontent.com/90501635/203612938-ca8c5233-b5fd-4c2d-aedf-94f10dbfbf3f.png)

The output of the program should be a result of the following distances(in this order):
1. euclidean
2. manhattan
3. chebyshev
4. canberra
5. minkowsky

![image](https://user-images.githubusercontent.com/90501635/203612993-2ef00671-1ec5-47d8-926a-decb0e942784.png)
