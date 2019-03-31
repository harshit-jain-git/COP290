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

void Bike::draw()
{
    glColor3f(color.x, color.y, color.z);

    glPushMatrix();
    
    glTranslatef(position.x,position.y,0);

    glBegin(GL_POLYGON);
    glVertex3f(0,-width/2,0);
    glVertex3f(0,width/2,0);
    glVertex3f(length,width/2,0);
    glVertex3f(length,-width/2,0);
    glEnd();

    glBegin(GL_POLYGON);
    // glVertex3f(0,0,0);

    glVertex3f(0,width*2,0);
    glVertex3f(length/5.0,width*2,0);
    glVertex3f(length/5.0,-width*2,0);
    glVertex3f(0,-width*2,0);
    glEnd();

    glPopMatrix();
}