#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "Road.h"

void keyboardCallback(unsigned char key, int x, int y)
{
    if (key == GLFW_KEY_ESCAPE) {
        glutDestroyWindow(glutGetWindow());
    }
    return;
}

void display()
{

}


int main()
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0,0);
    glutKeyboardFunc(keyboardCallback);
    glutCreateWindow("Traffic Simulator");
    
    glClearColor(0.2, 0.6, 0.99, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho2D(0, WIDTH, 0, HEIGHT);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
    
}