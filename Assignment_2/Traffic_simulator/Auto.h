#ifndef AUTO_H
#define AUTO_H

#include "Tuple.h"
#include "Colors.h"
#include "graphics.h"
#include <GLFW/glfw3.h>
using namespace std;

class Auto
{
public:
    static float length;
    static float width;
    static Tuple acceleration;
    static float maxSpeed;
    static int count_per_sec;

    Tuple position;
    Tuple velocity;
    
    Tuple color;
    Tuple color2;
    
    int lane;
    int n_lanes;
    float dstToLight = 1.5;

    vector<int> lane_index;    

    Auto();
    Auto(Tuple pos);

    void draw();
    void print();
};

#endif