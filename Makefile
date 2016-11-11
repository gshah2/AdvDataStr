CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCEDIR1 = infra
ifeq ($(PROGRAM), proj1)
     SOURCEDIR2=Proj1
     EXECUTABLE=Proj1/proj1
endif
ifeq ($(PROGRAM), proj2)
     SOURCEDIR2=Proj2
     EXECUTABLE=Proj2/proj2
endif
ifeq ($(PROGRAM), proj3)
     SOURCEDIR2=Proj3
     EXECUTABLE=Proj3/proj3
endif
ifeq ($(PROGRAM), proj4)
    SOURCEDIR2=Proj4
    EXECUTABLE=Proj4/proj4
endif
SOURCES=$(wildcard $(SOURCEDIR2)/**/*.c) $(wildcard $(SOURCEDIR1)/*.c)
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
