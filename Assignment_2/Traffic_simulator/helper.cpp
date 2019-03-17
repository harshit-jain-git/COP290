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
            else if (str.compare("Road_Length"))
            {
                Road::length = stof(ans);
            }
            else if (str.compare("Road_Width"))
            {
                Road::width = stof(ans);
            }
            else if (str.compare("Road_Signal"))
            {
                Road::signal = stoi(ans);
            }
            else if (str.compare("Default_MaxSpeed"))
            {
                maxSpeed = stof(ans);                
            }
            else if (str.compare("Default_Acceleration"))
            {
                maxAcceleration = stof(ans);
            }
            else if (str.compare("Vehicle_Type"))
            {
                if (ans.compare("Car") == 0)
                {
                    getline(file, str);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Car::length = stof(ans);

                    getline(file, str);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Car::width = stof(ans);
                }
                else if (ans.compare("Bus") == 0)
                {
                    getline(file, str);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bus::length = stof(ans);

                    getline(file, str);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bus::width = stof(ans);
                }
                else if (ans.compare("Truck") == 0)
                {
                    getline(file, str);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Truck::length = stof(ans);

                    getline(file, str);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Truck::width = stof(ans);
                }
                else if (ans.compare("Bike") == 0)
                {
                    getline(file, str);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bike::length = stof(ans);

                    getline(file, str);
                    pos = line.find(" = ");
                    ans = line.substr(pos + 3);
                    Bike::width = stof(ans);
                }
            }            
        }
    }
    return;
}