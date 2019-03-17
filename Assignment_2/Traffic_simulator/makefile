C=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -std=c++11 
LFLAGS= -m64 -Wl,-O1
LIBS= -lm -lGL -lglut -lGLU -lX11 -lpthread `pkg-config glfw3 --static --libs`

OBJS = app.o Car.o Bus.o Bike.o Tuple.o Road.o Colors.o graphics.o

project: $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o traffic $(LIBS)

clean: 
	rm -r *.o