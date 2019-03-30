#ifndef TRUCK_H
#define TRUCK_H

#include "Tuple.h"
#include "Colors.h"
#include "graphics.h"
#include "Vehicle.h"
#include <GLFW/glfw3.h>
using namespace std;

class Truck
{
public:
    static float length;
    static float width;
    static Tuple acceleration;

    Tuple position;
    Tuple velocity;
    
    Tuple color;
    float dstToLight = 1.5;
    int lane;
    int n_lanes;
    vector<int> lane_index;

    Truck();
    Truck(Tuple pos);

    float getXPos();
    float getYPos();
    Tuple getPos();
    void draw();
    void print();
};

#endif