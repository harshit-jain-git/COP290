#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "Car.h"
#include "Bus.h"
#include "Bike.h"
#include "Tuple.h"
#include "Road.h"
#include "random"
#include <ctime>

using namespace std;

float roadWidth;
float roadColor;

time_t startTime;
time_t timer;

void error_callback(int error, const char* description)
{
    cerr << "Error: " << description << endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Tuple pos = Tuple(0.7,0.375,0);
Road road = Road();

void display()
{
    glLoadIdentity();
    road.draw();
    time(&timer);
    for (int i = 0; i < road.cars[1].size(); i++)
    {
        road.cars[1].at(i).position.x += (-0.01 * 1);
        road.cars[1].at(i).draw();
    }
    if (difftime(timer, startTime) > 1)
    {
        time(&startTime);
        for (int i = 0; i < 4; i++)
        {
            Tuple pos = Tuple(1, -0.375 + 0.25*i, 0);
            Car car = Car(pos);
            road.cars[i].push_back(car);
        }
    }
}

int main() {

    time(&startTime);
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    if (!glfwInit())
    {
        // Initialization failed
        cerr << "Initialization failed" << endl;
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Traffic Simulation", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        cerr << "Window or OpenGL context creation failed" << endl;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // ifstream file;
    // file.open("config.txt");
    // while(!file.eof())
    // {
        
    // }

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.f, 1.f, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        
        road.update();
        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}