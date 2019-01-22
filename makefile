MKLROOT = /opt/intel/mkl
CC=g++
CFLAGS= -pthread -DMKL_ILP64 -m64 -I/opt/intel/mkl/include -I.
LFLAGS=  -lblas -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_ilp64.a $(MKLROOT)/lib/intel64/libmkl_gnu_thread.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lgomp -lpthread -lm -ldl 
DEPS = helper.h mkl1.h cblas1.h pthread1.h
OBJ = helper.o conv.o pthread1.o mkl1.o cblas1.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

# pthread: pthread.o
# 	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)