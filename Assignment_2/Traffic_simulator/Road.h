#ifndef ROAD_H
#define ROAD_H

#define WIDTH 1920
#define HEIGHT 1080

#include "Tuple.h"
#include <iostream>
#include "Car.h"
#include "Bus.h"
#include "Truck.h"
#include "Bike.h"
#include <vector>
#include <GLFW/glfw3.h>

#define TLPOSITION -0.5

class Road
{
public:
    static Tuple roadColor;
    static int signal;

    static float length;
    static float width;
    static int id;

    vector<Car> cars;
    vector<Bus> buses;
    vector<Truck> trucks;
    vector<Bike> bikes;

    vector<float> lane1;
    vector<float> lane2;
    vector<float> lane3;

    Road();
    void draw();
    void update();
};

#endif