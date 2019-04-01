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

void Truck::draw()
{
    glColor3f(color.x, color.y, color.z);

    glPushMatrix();
    
    glTranslatef(0, -0.04, 0);
    glTranslatef(position.x,position.y,0);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, width*0.7, 0);
    glVertex3f(length, width*0.7, 0);
    glVertex3f(length, 0, 0);
    glEnd();

    //Top Part
    glBegin(GL_POLYGON);
    glVertex3f(length*0.2, width*0.7, 0);
    glVertex3f(length*0.2, width, 0);
    glVertex3f(length*0.1, width, 0);
    glVertex3f(0, width*0.7, 0);
    glEnd();
    glPopMatrix();
    return;
}