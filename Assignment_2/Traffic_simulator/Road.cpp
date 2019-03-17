#include "Road.h"

Tuple Road::roadColor = Tuple(1, 1, 1);

Road::Road()
{
    length = 1;
    width = 0.5;
}

void Road::draw()
{
    glColor3f(roadColor.x, roadColor.y, roadColor.z);
    glBegin(GL_POLYGON);
    glVertex3f(-length, -width, 0);
    glVertex3f(-length, width, 0);
    glVertex3f(length, width, 0);
    glVertex3f(length, -width, 0);
    glEnd();

    glColor3f(0, 1, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-length, -1, 0);
    glVertex3f(-length, -0.5, 0);
    glVertex3f(length, -0.5, 0);
    glVertex3f(length, -1, 0);
    glEnd();
    
    glColor3f(0, 1, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-length, 0.5, 0);
    glVertex3f(-length, 0.8, 0);
    glVertex3f(length, 0.8, 0);
    glVertex3f(length, 0.5, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-0.9, -0.025, 0);
    glVertex3f(-0.9, 0.025, 0);
    glVertex3f(-0.5, 0.025, 0);
    glVertex3f(-0.5, -0.025, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-0.2, -0.025, 0);
    glVertex3f(-0.2, 0.025, 0);
    glVertex3f(0.2, 0.025, 0);
    glVertex3f(0.2, -0.025, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.5, -0.025, 0);
    glVertex3f(0.5, 0.025, 0);
    glVertex3f(0.9, 0.025, 0);
    glVertex3f(0.9, -0.025, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-0.8, -0.25, 0);
    glVertex3f(-0.6, -0.25, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-0.4, -0.25, 0);
    glVertex3f(-0.2, -0.25, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0, -0.25, 0);
    glVertex3f(0.2, -0.25, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.4, -0.25, 0);
    glVertex3f(0.6, -0.25, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-0.8, 0.25, 0);
    glVertex3f(-0.6, 0.25, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-0.4, 0.25, 0);
    glVertex3f(-0.2, 0.25, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0, 0.25, 0);
    glVertex3f(0.2, 0.25, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.4, 0.25, 0);
    glVertex3f(0.6, 0.25, 0);
    glEnd();
}

void Road::update()
{
    
}
