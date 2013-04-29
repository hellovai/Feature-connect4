CC=g++
CFLAGS=-c -W
LDFLAGS=
SOURCES=main.cpp game.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tic-tac-toe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	mv $(EXECUTABLE) ../

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

