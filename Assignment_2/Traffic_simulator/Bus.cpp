#include "Bus.h"

using namespace std;

Bus::Bus(Tuple pos)
{
    position = Tuple();
    velocity = Tuple();
    color = Colors::getRandomColor();

    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    velocity.x = 0.6;
}

Bus::Bus()
{
    position = Tuple();
    velocity = Tuple();
    color = Colors::getRandomColor();
}

float Bus::getXPos()
{
    return position.x;
}

float Bus::getYPos()
{
    return position.y;
}

Tuple Bus::getPos()
{
    return position;
}

void Bus::draw()
{
    glPushMatrix();

    glTranslatef(position.x, position.y, 0);

    glColor3f(color.x, color.y, color.z);
    glPushMatrix();
    // rotateY(-busAngle / 1.3);
    glTranslatef(-0.2,0,0);
    drawCube(length,width,0.135);
    glColor3f(0,0.8,0.8);
    glTranslatef(-0.02,0.02,0);
    drawCube(length - 0.05,width/2.0,0.14);
    glPopMatrix();

    glPopMatrix();
}