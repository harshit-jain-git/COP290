#ifndef ROAD_H
#define ROAD_H

#define WIDTH 1920
#define HEIGHT 1080

#include "Tuple.h"
#include <iostream>
#include "Car.h"
#include <vector>
#include <GLFW/glfw3.h>

class Road
{
public:
    static Tuple roadColor;

    float length;
    float width;
    int id;
    int signal;

    vector<Car> cars[4];
    Road();
    void draw();
    void update();
};

#endif