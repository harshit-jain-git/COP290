#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "Car.h"
#include "Bus.h"
#include "Bike.h"
#include "Truck.h"
#include "Tuple.h"
#include "Road.h"
#include <ctime>
#include "helper.h"

using namespace std;
float roadWidth;
float roadColor;

time_t startTime;
time_t timer;

int count[4] = {0};

int Road::signal;
Tuple Car::acceleration = Tuple(0.01, 0, 0);
Tuple Bike::acceleration = Tuple(0.01, 0, 0);
Tuple Truck::acceleration = Tuple(0.005, 0, 0);
Tuple Bus::acceleration = Tuple(0.005, 0, 0);

void error_callback(int error, const char* description)
{
    cerr << "Error: " << description << endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Road road = Road();

void display()
{
    glLoadIdentity();
    road.draw();
    tc();
    light(road.signal);
    time(&timer);
    for (int i = 0; i < road.cars.size(); i++)
    {
        float position_x = road.cars.at(i).position.x;
        float velocity_x = road.cars.at(i).velocity.x;
        float dst = road.cars.at(i).dstToLight;
        int lan = road.cars.at(i).lane;
        int lan_index = road.cars.at(i).lane_index;

        road.cars.at(i).position.x += (-0.01 * velocity_x);
        road.lanes[lan].at(lan_index) = road.cars.at(i).position.x;

        if (lan_index != 0) road.cars.at(i).dstToLight = -road.lanes[lan].at(lan_index - 1) + road.cars.at(i).position.x;
        else road.cars.at(i).dstToLight = road.cars.at(i).position.x - TLPOSITION;

        if (road.cars.at(i).dstToLight <= 0.05) road.cars.at(i).velocity.x = 0;
        else if (velocity_x > 0.3 && road.signal > 0) road.cars.at(i).velocity.x -= (Car::acceleration.x);
        else if (velocity_x > 0 && velocity_x < 1 && road.signal == 0) road.cars.at(i).velocity.x += (Car::acceleration.x);
        
        road.cars.at(i).draw();
    }
    for (int i = 0; i < road.buses.size(); i++)
    {
        float position_x = road.buses.at(i).position.x;
        float velocity_x = road.buses.at(i).velocity.x;
        float dst = road.buses.at(i).dstToLight;
        int lan = road.buses.at(i).lane;
        int lan_index = road.buses.at(i).lane_index;

        road.buses.at(i).position.x += (-0.01 * velocity_x);
        road.lanes[lan].at(lan_index) = road.buses.at(i).position.x;

        if (lan_index != 0) road.buses.at(i).dstToLight = -road.lanes[lan].at(lan_index - 1) + road.buses.at(i).position.x;
        else road.buses.at(i).dstToLight = road.buses.at(i).position.x - TLPOSITION;

        if (road.buses.at(i).dstToLight <= 0.05 && road.signal > 0) road.buses.at(i).velocity.x = 0;
        else if (velocity_x > 0.3 && road.signal > 0) road.buses.at(i).velocity.x -= (Bus::acceleration.x);
        else if (velocity_x > 0 && velocity_x < 1 && road.signal == 0) road.buses.at(i).velocity.x += (Bus::acceleration.x);
        
        road.buses.at(i).draw();
    }
    for (int i = 0; i < road.trucks.size(); i++)
    {
        float position_x = road.trucks.at(i).position.x;
        float velocity_x = road.trucks.at(i).velocity.x;
        float dst = road.trucks.at(i).dstToLight;
        int lan = road.trucks.at(i).lane;
        int lan_index = road.trucks.at(i).lane_index;
        
        road.trucks.at(i).position.x += (-0.01 * velocity_x);
        road.lanes[lan].at(lan_index) = road.trucks.at(i).position.x;

        if (lan_index != 0) road.trucks.at(i).dstToLight = road.lanes[lan].at(lan_index - 1);
        else road.trucks.at(i).dstToLight = road.trucks.at(i).position.x - TLPOSITION;

        if (road.trucks.at(i).dstToLight <= 0.05 && road.signal > 0) road.trucks.at(i).velocity.x = 0;
        else if (velocity_x > 0.3 && road.signal > 0) road.trucks.at(i).velocity.x -= (Truck::acceleration.x);
        else if (velocity_x > 0 && velocity_x < 1 && road.signal == 0) road.trucks.at(i).velocity.x += (Truck::acceleration.x);
        
        road.trucks.at(i).draw();
    }
    for (int i = 0; i < road.bikes.size(); i++)
    {
        float position_x = road.bikes.at(i).position.x;
        float velocity_x = road.bikes.at(i).velocity.x;
        float dst = road.bikes.at(i).dstToLight;
        int lan = road.bikes.at(i).lane;
        int lan_index = road.bikes.at(i).lane_index;
        road.bikes.at(i).position.x += (-0.01 * velocity_x);
        road.lanes[lan].at(lan_index) = road.bikes.at(i).position.x;

        if (lan_index != 0) road.bikes.at(i).dstToLight = road.lanes[lan].at(lan_index - 1);
        else road.bikes.at(i).dstToLight = road.bikes.at(i).position.x - TLPOSITION;

        if (road.bikes.at(i).dstToLight <= 0.05 && road.signal > 0) road.bikes.at(i).velocity.x = 0;
        else if (velocity_x > 0.3 && road.signal > 0) road.bikes.at(i).velocity.x -= (Bike::acceleration.x);
        else if (velocity_x > 0 && velocity_x < 1 && road.signal == 0) road.bikes.at(i).velocity.x += (Bike::acceleration.x);
        
        road.bikes.at(i).draw();
    }

    if (difftime(timer, startTime) > 1)
    {
        time(&startTime);
        if (Road::signal > 0) Road::signal--;
        cout << Road::signal << endl;
        for (int i = 0; i < 4; i++)
        {
            if (road.lanes[i].size() > 0)
                if (road.lanes[i].back() > 0.6)
                    continue;
            Tuple pos = Tuple(1, -0.375 + 0.25*i, 0);
            int toss = rand()%4;
            if (toss == 0)
            {
                Car car = Car(pos);
                car.lane = i;
                car.lane_index = count[i];
                road.lanes[i].push_back(car.position.x);
                road.cars.push_back(car);
            }
            else if (toss == 1)
            {
                Bus bus = Bus(pos);
                bus.lane = i;
                bus.lane_index = count[i];
                road.lanes[i].push_back(bus.position.x);
                road.buses.push_back(bus);
            }
            else if (toss == 2)
            {
                Truck truck = Truck(pos);
                truck.lane = i;
                truck.lane_index = count[i];
                road.lanes[i].push_back(truck.position.x);
                road.trucks.push_back(truck);
            }
            else if (toss == 3)
            {
                Bike bike = Bike(pos);
                bike.lane = i;
                bike.lane_index = count[i];
                road.lanes[i].push_back(bike.position.x);
                road.bikes.push_back(bike);
            }   
            count[i]++;
        }
    }
}

int main() {
    
    load_configuration();
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