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
#include "Auto.h"

#define TLPOSITION -0.8
#define lane_width 0.05

class Road
{
public:
    static Tuple roadColor;
    static int signal;

    static float length;
    static float width;
    static int id;
    static float maxSpeed;
    static float maxAcceleration;
    static int num_lanes;

    vector<Car> cars;
    vector<Bus> buses;
    vector<Truck> trucks;
    vector<Bike> bikes;
    vector<Auto> autos;
    vector<float>*  lanes;
    int* start_index;
    static int rows;

    static char** console;

    Road();
    void draw();
    void update();
};

#endif