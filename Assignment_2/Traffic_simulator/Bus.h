#ifndef BUS_H
#define BUS_H

#include "Tuple.h"
#include "Colors.h"
#include "graphics.h"
#include <GLFW/glfw3.h>
#include "Vehicle.h"
using namespace std;

class Bus
{
public:
    static float length;
    static float width;
    static Tuple acceleration;

    Tuple position;
    Tuple velocity;
    
    Tuple color;
    float dstToLight = 1.5;

    Bus();
    Bus(Tuple pos);

    float getXPos();
    float getYPos();
    Tuple getPos();
    void draw();

    void print();
};

#endif