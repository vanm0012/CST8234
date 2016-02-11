# Makefile for: 
# Author: 	Tryton Van Meer

CC=gcc
CFLAGS=-c -Wall
CLIBS=-lglut -lGL -lGLU -lm
SOURCES=src/particles_OpenGL.c src/vanmeer_particle.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=build/particles

all: $(SOURCES) $(EXECUTABLE)

debug: CFLAGS += -g
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	if [ ! -d "./build" ]; then mkdir build; fi
	$(CC) $(OBJECTS) -o $@ $(CLIBS)

.c:.o
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f src/*.o src/*.h.gch $(EXECUTABLE)
	rmdir build
