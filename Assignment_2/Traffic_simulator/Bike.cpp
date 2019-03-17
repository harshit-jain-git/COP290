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
    glTranslatef(0, 0, 0);
    glColor3f(color.x, color.y, color.z);

    glPushMatrix();
    glTranslatef(position.x,position.y,0);
    glPushMatrix();

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(0,0.05,0);
    glVertex3f(0.1,0.05,0);
    glVertex3f(0.1,0,0);
    glEnd();

    glBegin(GL_POLYGON);
    // glVertex3f(0,0,0);

    glVertex3f(0,0.08,0);
    glVertex3f(0.02,0.08,0);
    glVertex3f(0.02,-0.03,0);
    glVertex3f(0,-0.03,0);
    glEnd();

    glPopMatrix();

    glPopMatrix();
}