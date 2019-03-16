#include "Vehicle.h"
#include "Tuple.h"

Vehicle::Vehicle(int l, int w)
{
    length = l;
    width = w;
    position = Tuple();
    velocity = Tuple();
    acceleration = Tuple();
    color = Colors::getRandomColor();
}

float Vehicle::getXPos()
{
    return position.x;
}

float Vehicle::getYPos()
{
    return position.y;
}

Tuple Vehicle::getPos()
{
    return position;
}

void Car::draw()
{

}

void Bus::draw()
{

}

void Bike::draw()
{
    
}
