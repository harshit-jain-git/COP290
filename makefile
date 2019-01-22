MKLROOT = /home/co/intel/mkl
CC=g++
CFLAGS= -pthread -DMKL_ILP64 -m64 -I/home/co/intel/mkl/include -I.
LFLAGS=  -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_ilp64.a $(MKLROOT)/lib/intel64/libmkl_gnu_thread.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lgomp -lpthread -lm -ldl
DEPS = helper.h
OBJ = helper.o conv.o pthread.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

pthread: pthread.o
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)