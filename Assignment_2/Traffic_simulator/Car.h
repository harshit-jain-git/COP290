#ifndef CAR_H
#define CAR_H

#include "Tuple.h"
#include "Colors.h"
#include "graphics.h"
#include "Vehicle.h"
#include <GLFW/glfw3.h>
using namespace std;

class Car : public Vehicle
{
public:
    static float length;
    static float width;

    Tuple position;
    Tuple velocity;
    Tuple acceleration;
    float dstToNext;

    Tuple color;

    Car();
    Car(Tuple pos);

    float getXPos();
    float getYPos();
    Tuple getPos();
    void draw();
    void print();
};

#endif