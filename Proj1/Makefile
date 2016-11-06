CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=$(shell find . -name '*.c')
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=assn_1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)
