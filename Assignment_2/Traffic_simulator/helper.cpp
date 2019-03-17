#include <iostream>
#include <fstream>
#include <string>
#include "Road.h"
#include "Truck.h"
#include "helper.h"
#include "Bike.h"
#include "Bus.h"
#include "Car.h"

using namespace std;

int Road::id;
float Road::length;
float Road::width;
float Car::length;
float Car::width;
float Bus::length;
float Bus::width;
float Truck::length;
float Truck::width;
float Bike::length;
float Bike::width;
float maxSpeed;
float maxAcceleration;

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
                maxSpeed = stof(ans);                
            }
            else if (str.compare("Default_Acceleration") == 0)
            {
                maxAcceleration = stof(ans);
            }
            else if (str.compare("Vehicle_Type") == 0)
            {
                if (ans.compare("Car") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Car::length = stof(ans);

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Car::width = stof(ans);
                }
                else if (ans.compare("Bus") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bus::length = stof(ans);

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bus::width = stof(ans);
                }
                else if (ans.compare("Truck") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Truck::length = stof(ans);

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Truck::width = stof(ans);
                }
                else if (ans.compare("Bike") == 0)
                {
                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bike::length = stof(ans);

                    getline(file, line);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bike::width = stof(ans);
                }
            }            
        }
        cout << line << endl;
    }
    return;
}