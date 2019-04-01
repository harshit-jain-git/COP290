#include <iostream>
#include <fstream>
#include <string>
#include "Road.h"
#include "Truck.h"
#include "helper.h"
#include "Bike.h"
#include "Bus.h"
#include "Car.h"
#include "Auto.h"

using namespace std;

int Road::id;
float Road::length;
float Road::width;
int Road::num_lanes;
char** Road::console;
int Road::rows;
float Car::length;
float Car::width;
float Bus::length;
float Bus::width;
float Truck::length;
float Truck::width;
float Bike::length;
float Bike::width;
float Road::maxSpeed;
float Road::maxAcceleration;
float Auto::length;
float Auto::width;
float Auto::maxSpeed;

float Bike::maxSpeed;
float Car::maxSpeed;
float Bus::maxSpeed;
float Truck::maxSpeed;

void tc()
{
    glLoadIdentity();
    glColor3f(0.0,0.0,0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-0.7,-0.5,0);
    glVertex3f(-0.7,-0.1,0);
    glVertex3f(-0.65,-0.1,0);
    glVertex3f(-0.65,-0.5,0);
    glEnd();
}

void light(int a)
{   
    glLoadIdentity();
    if(a>0)
        glColor3f(1.0,0.0,0.0);
    else
    {
        glColor3f(0.0,1.0,0.0);
    }
    
    glBegin(GL_POLYGON);
    glVertex3f(-0.695,-0.25,0);
    glVertex3f(-0.695,-0.2,0);
    glVertex3f(-0.655,-0.2,0);
    glVertex3f(-0.655,-0.25,0);
    glEnd();
}

void load_configuration(){
    ifstream file;
    string line;
    file.open("config.txt", ios::in);

    while(!file.eof())
    {
        getline(file, line);
        int pos = line.find(" = ");
        if (pos < line.size()) {
            string str = line.substr(0, pos);
            string ans = line.substr(pos + 3);

            if (str.compare("Road_Id") == 0)
            {
                Road::id = stoi(ans);
            }
            else if (str.compare("Road_Length") == 0)
            {
                Road::length = stof(ans);
            }
            else if (str.compare("Road_Width") == 0)
            {
                Road::width = stof(ans);
            }
            else if (str.compare("Road_Signal") == 0)
            {
                Road::signal = stoi(ans);
            }
            else if (str.compare("Default_MaxSpeed") == 0)
            {
                Road::maxSpeed = stof(ans);                
            }
            else if (str.compare("Default_Acceleration") == 0)
            {
                Road::maxAcceleration = stof(ans);
            }
            else if (str.compare("Vehicle_Type") == 0)
            {
                if (ans.compare("Car") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Car::length = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Car::width = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Car::maxSpeed = stof(ans);
                }
                else if (ans.compare("Bus") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bus::length = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bus::width = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bus::maxSpeed = stof(ans);
                }
                else if (ans.compare("Truck") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Truck::length = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Truck::width = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Truck::maxSpeed = stof(ans);
                }
                else if (ans.compare("Bike") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bike::length = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bike::width = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bike::maxSpeed = stof(ans);
                }
                else if (ans.compare("Auto") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Auto::length = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Auto::width = stof(ans)*0.05;

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Auto::maxSpeed = stof(ans);
                }
            }            
        }
        else 
        {
            int p = line.find(" ");
            if (p < line.size())
            {
                string str = line.substr(0, p);
                string ans = line.substr(p + 1);
                cout << str << endl;
                if (str.compare("Pass") == 0) break;
                else if (str.compare("Car") == 0)
                    Car::count_per_sec++;
                else if (str.compare("bike") == 0)
                    Bike::count_per_sec++;
                else if (str.compare("Bus") == 0)
                    Bus::count_per_sec++;
                else if (str.compare("Truck") == 0)
                    Truck::count_per_sec++;
                else if (str.compare("Auto") == 0)
                    Auto::count_per_sec++;                
            }
            cout << line << endl;
        }
    }
    Road::num_lanes = (int)(2*Road::width/lane_width);
    int length = (int)(2*Road::width/0.05);
    Road::rows = length/2;
    Road::console = new char*[length];
    for (int i = 0; i < length; i++)
        Road::console[i] = new char[40];
    return;
}