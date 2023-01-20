# Chooses the right compiler.
CC = g++ -std=c++11 -pthread
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif
BUILD_FILES += distance_metric.o
BUILD_FILES += knn.o
BUILD_FILES += reader_class.o
BUILD_FILES += database.o
BUILD_FILES += input_validation.o
BUILD_FILES += cli.o
BUILD_FILES += command.o
BUILD_FILES += socketIO.o

all: $(BUILD_FILES) server_side.o client.o
	$(CC) $(BUILD_FILES) server_side.o -o server.out
	$(CC) $(BUILD_FILES) client.o -o client.out

run: $(BUILD_FILES) server_side.o client.o
	$(CC) $(BUILD_FILES) server_side.o -o server.out & $(CC) $(BUILD_FILES) client.o -o client.out

# Build the algs folder
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

server_side.o: server_side.cpp
	$(CC) -c -o server_side.o server_side.cpp
client.o: client.cpp
	$(CC) -c -o client.o client.cpp

# Clean command
clean:
	$(CLN) *.o server.out client.out