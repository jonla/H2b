
CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lm

HEADERS =
OBJECTS = func.o main.o
PROGRAM = run

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
	touch *.c

