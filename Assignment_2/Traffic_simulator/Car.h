#ifndef CAR_H
#define CAR_H

#include "Tuple.h"
#include "Colors.h"
#include "graphics.h"
#include <GLFW/glfw3.h>
using namespace std;

class Car
{
public:
    static float length;
    static float width;
    static Tuple acceleration;

    Tuple position;
    Tuple velocity;
    float dstToNext;

    Tuple color;
    float dstToLight = 1.5;

    Car();
    Car(Tuple pos);

    float getXPos();
    float getYPos();
    Tuple getPos();
    void draw();
    void print();
};

#endif