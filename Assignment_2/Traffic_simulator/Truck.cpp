#include "Truck.h"

using namespace std;

Truck::Truck(Tuple pos)
{
    position = Tuple();
    velocity = Tuple();
    color = Colors::getRandomColor();

    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    velocity.x = 0.5;
}

Truck::Truck()
{
    position = Tuple();
    velocity = Tuple();
    color = Colors::getRandomColor();
}

float Truck::getXPos()
{
    return position.x;
}

float Truck::getYPos()
{
    return position.y;
}

Tuple Truck::getPos()
{
    return position;
}

void Truck::draw()
{
    return;
}