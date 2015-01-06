CC=g++
CFLAGS=-std=gnu++11 -c -g -Wall
LFLAGS=
SOURCES=Buffer.cpp Image.cpp Capture.cpp Controller.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=capture

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o bin/$@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
