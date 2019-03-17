#include "Bike.h"

using namespace std;

Bike::Bike(Tuple pos)
{
    position = Tuple();
    velocity = Tuple();
    color = Colors::getRandomColor();

    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    velocity.x = 0.9;
}

float Bike::getXPos()
{
    return position.x;
}

float Bike::getYPos()
{
    return position.y;
}

Tuple Bike::getPos()
{
    return position;
}

void Bike::draw()
{
    
}