CC=g++
CFLAGS=-std=gnu++11 -c -g -Wall
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=Buffer.cpp Image.cpp Capture.cpp Controller.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=capture

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
