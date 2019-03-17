#include "Bus.h"

using namespace std;

Bus::Bus(Tuple pos)
{
    position = Tuple();
    velocity = Tuple();
    acceleration = Tuple();
    color = Colors::getRandomColor();

    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
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

    glTranslatef(0,0.07,0);

    glColor3f(color.x, color.y, color.z);
    glPushMatrix();
    // rotateY(-busAngle / 1.3);
    glTranslatef(-0.2,0,0);
    drawCube(0.3,0.13,0.135);
    glColor3f(0,0.8,0.8);
    glTranslatef(-0.02,0.02,0);
    drawCube(0.25,0.07,0.14);
    glPopMatrix();

    glColor3f(color.x, color.y, color.z);
    glPushMatrix();

    // rotateY(busAngle / 4);
    glTranslatef(0.2,0,0);
    drawCube(0.3, 0.13, 0.135);
    glColor3f(0,0.8,0.8);
    glTranslatef(0.02,0.02,0);
    drawCube(0.27,0.07,0.14);
    glPopMatrix();

    glColor3f(0.5,0.5,0);
    drawCube(0.2,0.12,0.12);

    glPushMatrix();

    glPopMatrix();
    glPopMatrix();
}