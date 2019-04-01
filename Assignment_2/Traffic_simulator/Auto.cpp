#include "Auto.h"

using namespace std;

Auto::Auto(Tuple pos)
{
    position = Tuple();
    velocity = Tuple();
    color = Colors::getRandomColor();
    color2 = Colors::getRandomColor();

    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    velocity.x = 0.9;
}

void Auto::draw()
{
    glColor3f(color.x, color.y, color.z);

    glPushMatrix();
    
    glTranslatef(position.x,position.y,0);

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(length*0.2,width/2,0);
    glVertex3f(length,width/2,0);
    glVertex3f(length,-width/2,0);
    glVertex3f(length*0.2,-width/2,0);
    glEnd();

    glColor3f(color2.x, color2.y, color2.z);
    glBegin(GL_POLYGON);
    // glVertex3f(0,0,0);

    glVertex3f(length*0.25,width/2.5,0);
    glVertex3f(length*0.9,width/2.5,0);
    glVertex3f(length*0.9,-width/2.5,0);
    glVertex3f(length*0.25,-width/2.5,0);
    glEnd();

    glPopMatrix();
}