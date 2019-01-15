CC=g++
CFLAGS=-I.
DEPS = helper.h
OBJ = helper.o conv.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)