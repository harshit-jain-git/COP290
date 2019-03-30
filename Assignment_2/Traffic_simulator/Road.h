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
#include "helper.h"

#define TLPOSITION -0.5
#define lane_width 0.25

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
    static int num_lanes;
    vector<float>*  lanes;

    Road();
    void draw();
    void update();
};

#endif