#include "Road.h"

Tuple Road::roadColor = Tuple(1, 1, 1);

Road::Road()
{
    length = 2;
    width = 0.5;
}

void Road::draw()
{
    glLoadIdentity();
    glColor3f(roadColor.x, roadColor.y, roadColor.z);
    glBegin(GL_POLYGON);
    glVertex3f(-length, -width, 0);
    glVertex3f(-length, width, 0);
    glVertex3f(length, width, 0);
    glVertex3f(length, -width, 0);
    glEnd();

    glLoadIdentity();
    glColor3f(0, 1, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-length, -1, 0);
    glVertex3f(-length, -0.5, 0);
    glVertex3f(length, -0.5, 0);
    glVertex3f(length, -1, 0);
    glEnd();
    
    glLoadIdentity();
    glColor3f(0, 1, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-length, 0.5, 0);
    glVertex3f(-length, 0.8, 0);
    glVertex3f(length, 0.8, 0);
    glVertex3f(length, 0.5, 0);
    glEnd();
    
    glLoadIdentity();
    glColor3f(0, 0.7, 1);
    glBegin(GL_POLYGON);
    glVertex3f(-length, 0.8, 0);
    glVertex3f(-length, 1, 0);
    glVertex3f(length, 1, 0);
    glVertex3f(length, 0.8, 0);
    glEnd();

    glLoadIdentity();
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-1, -0.05, 0);
    glVertex3f(-1, 0.05, 0);
    glVertex3f(-0.6, 0.05, 0);
    glVertex3f(-0.6, -0.05, 0);
    glEnd();

    glLoadIdentity();
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-0.2, -0.05, 0);
    glVertex3f(-0.2, 0.05, 0);
    glVertex3f(0.2, 0.05, 0);
    glVertex3f(0.2, -0.05, 0);
    glEnd();

    glLoadIdentity();
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.6, -0.05, 0);
    glVertex3f(0.6, 0.05, 0);
    glVertex3f(1, 0.05, 0);
    glVertex3f(1, -0.05, 0);
    glEnd();

}
