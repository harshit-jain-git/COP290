#ifndef VEHICLE_H
#define VEHICLE_H

#include "ds.h"
using namespace std;

class Vehicle
{
public:
    float velocity;
    float acceleration;
    float length;
    float width;

    float getXPos();
    float getYPos();
    float getDstToCross();
};

class Car : public Vehicle
{
    public:
        void update();
        void draw();
}

class Bus : public Vehicle
{
    public:
        void update();
        void draw();
}

#endif