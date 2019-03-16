MKLROOT = /opt/intel/mkl
CC=g++ -std=c++11
CFLAGS= -pthread -DMKL_ILP64 -m64 -I$(MKLROOT)/include -I.
LFLAGS=  -lblas -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_ilp64.a $(MKLROOT)/lib/intel64/libmkl_gnu_thread.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lgomp -lpthread -lm -ldl 
DEPS = helper.h pthread_multiply.h mkl_multiply.h cblas_multiply.h
OBJ = helper.o conv.o pthread_multiply.o mkl_multiply.o cblas_multiply.o
OBJ_2 = pthread_multiply.o mkl_multiply.o cblas_multiply.o performance.o
OBJ_3 = pthread_multiply.o mkl_multiply.o cblas_multiply.o lenet.o helper.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

performance: $(OBJ_2)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

lenet: $(OBJ_3)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
clean:
	rm -f *.o 
