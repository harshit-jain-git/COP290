#include "Car.h"

using namespace std;

Car::Car(Tuple pos)
{
    position = Tuple();
    velocity = Tuple();
    acceleration = Tuple();
    color = Colors::getRandomColor();

    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
}

float Car::getXPos()
{
    return position.x;
}

float Car::getYPos()
{
    return position.y;
}

Tuple Car::getPos()
{
    return position;
}

void drawQuad(Tuple a, Tuple b, Tuple c, Tuple d)
{
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glVertex3f(c.x, c.y, c.z);
    glVertex3f(d.x, d.y, d.z);
}

void drawRoof()
{
    Tuple a1(0,0,-0.05);
    Tuple a2(0.025,0.05,-0.0375);
    Tuple a3(0.075,0.05,-0.0375);
    Tuple a4(0.1125,0,-0.05);
    Tuple a5(0,0,0.05);
    Tuple a6(0.025,0.05,0.0375);
    Tuple a7(0.075,0.05,0.0375);
    Tuple a8(0.1125,0,0.05);

    glPushMatrix();
    glTranslatef(-0.075, 0.025, 0);
    glBegin(GL_QUADS);

    drawQuad(a2,a6,a7,a3);

    glColor3f(0,1,1);

    drawQuad(a1,a2,a3,a4);
    drawQuad(a1,a5,a6,a2);
    drawQuad(a5,a8,a7,a6);
    drawQuad(a8,a4,a3,a7);

    glEnd();
    glPopMatrix();
}

void Car::draw()
{
    glTranslatef(0, 0, 0);
    glColor3f(color.x, color.y, color.z);

    glPushMatrix();
    glTranslatef(position.x,position.y,0);
    drawCube(0.2,0.05,0.1);
    drawRoof();

    glPopMatrix();
}

