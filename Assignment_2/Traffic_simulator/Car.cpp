#include "Car.h"

using namespace std;

Car::Car(Tuple pos)
{
    position = Tuple();
    velocity = Tuple();
    color = Colors::getRandomColor();

    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    velocity.x = 1;
}

Car::Car()
{
    position = Tuple();
    velocity = Tuple();
    color = Colors::getRandomColor();
}

void drawQuad(Tuple a, Tuple b, Tuple c, Tuple d)
{
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glVertex3f(c.x, c.y, c.z);
    glVertex3f(d.x, d.y, d.z);
}

void Car::draw()
{
    glPushMatrix();

    glTranslatef(position.x, position.y, 0);
    glColor3f(color.x, color.y, color.z);

    glBegin(GL_POLYGON);
    glVertex3f(0, -width/2, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(length, 0, 0);
    glVertex3f(length, -width/2, 0);
    glEnd();

    glColor3f(0, 1, 1);

    glBegin(GL_POLYGON);
    glVertex3f(length/8, 0, 0);
    glVertex3f(length*2/8, width*1.2/2, 0);
    glVertex3f(length*5/8, width*1.2/2, 0);
    glVertex3f(length*6/8, 0, 0);
    glEnd();

    glPopMatrix();
}

