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
    glTranslatef(position.x,position.y,0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0.1, 0);
    glVertex3f(0.2, 0.1, 0);
    glVertex3f(0.2, 0, 0);
    glEnd();

    //Top Part
    glBegin(GL_POLYGON);
    glVertex3f(0.02, 0.1, 0);
    glVertex3f(0.02, 0.15, 0);
    glVertex3f(0.01, 0.15, 0);
    glVertex3f(0, 0.1, 0);
    glEnd();
    return;
}