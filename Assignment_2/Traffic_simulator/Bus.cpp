#include "Bus.h"

using namespace std;

Bus::Bus(Tuple pos)
{
    position = Tuple();
    velocity = Tuple();
    color_1 = Colors::getRandomColor();
    color_2 = Colors::getRandomColor();

    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    velocity.x = 0.6;
}

Bus::Bus()
{
    position = Tuple();
    velocity = Tuple();
    color_1 = Colors::getRandomColor();
    color_2 = Colors::getRandomColor();
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

    glColor3f(color_1.x, color_1.y, color_1.z);
    glBegin(GL_POLYGON);
    glVertex3f(0, -width/2, 0);
    glVertex3f(0, width/2, 0);
    glVertex3f(length, width/2, 0);
    glVertex3f(length, -width/2, 0);
    glEnd();

    glColor3f(color_2.x, color_2.y, color_2.z);
    glBegin(GL_POLYGON);
    glVertex3f(length/15, -width/5, 0);
    glVertex3f(length/15, width/2.5, 0);
    glVertex3f(length*6/7, width/2.5, 0);
    glVertex3f(length*6/7, -width/5, 0);
    glEnd();

    glPopMatrix();
}