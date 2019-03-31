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
    static float maxSpeed;

    Tuple position;
    Tuple velocity;
    
    Tuple color;
    float dstToLight = 1.5;
    int lane;
    int n_lanes;
    vector<int> lane_index;

    Truck();
    Truck(Tuple pos);

    void draw();
    void print();
};

#endif