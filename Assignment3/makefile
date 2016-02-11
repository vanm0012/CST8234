# Makefile for: Assignment 3
# Author: 	    Tryton Van Meer

CC=gcc
CFLAGS=-Wall
SOURCES=cipher.c transpo.c
EXECUTABLE=$(basename $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): FORCE
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(EXECUTABLE) *.gch

PHONY: clean
FORCE:
