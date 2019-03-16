#ifndef ROAD_H
#define ROAD_H

#define WIDTH 1920
#define HEIGHT 1080

#include "Vehicle.h"
#include <algorithm>

class Vehicle;

class Road
{
public:
    Tuple roadColor;

    float length;
    float width;

    void draw();
}