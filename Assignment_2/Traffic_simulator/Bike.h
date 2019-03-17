#ifndef BIKE_H
#define BIKE_H

#include "Tuple.h"
#include "Colors.h"
#include "graphics.h"
#include "Vehicle.h"
#include <GLFW/glfw3.h>
using namespace std;

class Bike
{
public:
    static float length;
    static float width;

    Tuple position;
    Tuple velocity;
    Tuple acceleration;
    
    Tuple color;

    Bike();
    Bike(Tuple pos);

    float getXPos();
    float getYPos();
    Tuple getPos();
    void draw();
    void print();
};

#endif