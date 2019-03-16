#include "Road.h"
#include "Tuple.h"
#include <iostream>

Tuple Road::roadColor = Tuple(0.3, 0.3, 0.3);

Road::Road(int l, int w)
{
    length = l;
    width = w;
}

void Road::draw()
{
    glLoadIdentity();
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(0, HEIGHT/2 - width/2);
    glVertex2f(0, HEIGHT/2 + width/2);
    glVertex2f(WIDTH, HEIGHT/2 - width/2);
    glVertex2f(WIDTH, HEIGHT/2 - width/2);
    glEnd();
}
