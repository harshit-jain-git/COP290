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
    static Tuple acceleration;
    static float maxSpeed;

    Tuple position;
    Tuple velocity;
    
    Tuple color;
    
    int lane;
    int n_lanes;
    float dstToLight = 1.5;

    vector<int> lane_index;    

    Bike();
    Bike(Tuple pos);

    void draw();
    void print();
};

#endif