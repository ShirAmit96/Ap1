a.out: main.o database.o distance_metric.o input_managment.o input_validation.o knn.o reader_class.o
	g++ main.o database.o distance_metric.o input_managment.o input_validation.o knn.o reader_class.o -o a.out
 
main.o:
	g++ -c main.cpp	main.h

database.o:
	g++ -c database.cpp	database.h

distance_metric.o:
	g++ -c distance_metric.cpp	distance_metric.h

input_managment.o:
	g++ -c input_managment.cpp	input_managment.h

input_validation.o:
	g++ -c input_validation.cpp	input_validation.h

knn.o:
	g++ -c knn.cpp	knn.h
reader_class.o:
	g++ -c reader_class.cpp	reader_class.h
	
target: dependencies
	action

clean:
	rm *.o *h.gch a.out