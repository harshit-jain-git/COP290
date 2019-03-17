#ifndef ROAD_H
#define ROAD_H

#define WIDTH 1920
#define HEIGHT 1080

#include "Tuple.h"
#include <iostream>
#include <queue>
#include <GLFW/glfw3.h>

class Road
{
public:
    static Tuple roadColor;

    float length;
    float width;
    
    queue<void*> lane1;
    queue<void*> lane2;
    queue<void*> lane3;
    queue<void*> lane4;

    Road();
    void draw();

    
};

#endif