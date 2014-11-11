CC=g++
CFLAGS=-c -Wall -Werror -pedantic -O2 -std=c++0x
#-ggdb
LDFLAGS=-lrt
SOURCES=problema3.cpp tablero.cpp pieza.cpp
BACKTRACK1=backtracking1.cpp
BACKTRACK2=backtracking2.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=backtrack1 backtrack2 genRan

all: $(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

backtrack1: $(OBJECTS) $(BACKTRACK1:.cpp=.o)
	$(CC) $(OBJECTS) $(BACKTRACK1:.cpp=.o) $(LDFLAGS) -o backtrack1

backtrack2: $(OBJECTS) $(BACKTRACK2:.cpp=.o)
	$(CC) $(OBJECTS) $(BACKTRACK2:.cpp=.o) $(LDFLAGS) -o backtrack2

genRan: ejemplos_random.o
	$(CC) ejemplos_random.o $(LDFLAGS) -o genRan
	
#$(EXECUTABLE): $(OBJECTS)
#	$(CC) $(OBJECTS) $(LDFLAGS) -o $@


clean:
	rm -f *.o
	rm -f $(EXECUTABLE)

