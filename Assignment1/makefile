# Makefile for: C Lang Assignment 1
# Author: Tryton Van Meer

CC=gcc
CFLAGS=-c -Wall -ansi -pedantic
CLIBS=-lm
SOURCES=src/sms.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=build/Assignment1

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
