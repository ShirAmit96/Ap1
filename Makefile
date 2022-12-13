a.out: main.o database.o distance_metric.o input_managment.o input_validation.o knn.o reader_class.o
	g++ main.o database.o distance_metric.o input_managment.o input_validation.o knn.o reader_class.o -o a.out
 
main.o:
	g++ -std=c++11 -c main.cpp	main.h

database.o:
	g++ -std=c++11 -c database.cpp	database.h

distance_metric.o:
	g++ -std=c++11 -c distance_metric.cpp	distance_metric.h

input_managment.o:
	g++ -std=c++11 -c input_managment.cpp	input_managment.h

input_validation.o:
	g++ -std=c++11 -c input_validation.cpp	input_validation.h

knn.o:
	g++ -std=c++11 -c knn.cpp	knn.h
reader_class.o:
	g++ -std=c++11 -c reader_class.cpp	reader_class.h
	
target: dependencies
	action

clean:
	rm *.o *.h.gch a.out
