#ifndef VEHICLE_H
#define VEHICLE_H

#include "Tuple.h"
using namespace std;

class Vehicle
{
public:
    Tuple position;
    Tuple velocity;
    Tuple acceleration;
    float length;
    float width;
    Tuple color;

    float getXPos();
    float getYPos();
    Tuple getPos();
};

class Car : public Vehicle
{
    public:
        void draw();
}

class Bus : public Vehicle
{
    public:
        void draw();
}

class Bike : public Vehicle
{
    public:
        void draw();
}

#endif