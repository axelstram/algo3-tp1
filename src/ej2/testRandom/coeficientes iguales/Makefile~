CC=g++
CFLAGS=-c -Wall -Werror -pedantic -O2 -std=c++0x -ggdb
LDFLAGS=-lrt
SOURCES=ejemplos_random.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=testRan

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)
