# simple Makefile for mehl-server

CC=gcc
CFLAGS=-c -Wall --pedantic -g
LDFLAGS=-lpthread -g

BINDIR=/usr/bin

SOURCES=mehl.c list.c parser.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mehl-server

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

install:
	install --mode=775 $(EXECUTABLE) $(BINDIR)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

unistall:
	rm $(BINDIR)/$(EXECUTABLE)
