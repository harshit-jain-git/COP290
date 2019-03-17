#include <iostream>
#include <fstream>
#include <string>
#include "Road.h"
#include "Car.h"
#include "Bus.h"
#include "Bike.h"
#include "Truck.h"

using namespace std;

int maxSpeed;
int maxAcceleration;

Road road = Road();
int main(int argc, char** argv)
{
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
            cout << str << ' ' << ans << endl;

            if (str.compare("Road_Id") == 0)
            {
                road.id = stoi(ans);
            }
            else if (str.compare("Road_Length"))
            {
                road.length = stof(ans);
            }
            else if (str.compare("Road_Width"))
            {
                road.width = stof(ans);
            }
            else if (str.compare("Road_Signal"))
            {
                road.signal = stoi(ans);
            }
            else if (str.compare("Default_MaxSpeed"))
            {
                maxSpeed = stoi(ans);                
            }
            else if (str.compare("Default_Acceleration"))
            {
                maxAcceleration = stoi(ans);
            }
            else if (str.compare("Vehicle_Type"))
            {
                if (ans.compare("Car") == 0)
                {
                    getline(file, str);
                    int pos = line.find(" = ");
                    string ans = line.substr(pos + 3);
                    Car().length = stof(ans);

                    getline(file, str);
                    int pos = line.find(" = ");
                    string ans = line.substr(pos + 3);
                    Car().width = stof(ans);
                }
                else if (ans.compare("Bus") == 0)
                {
                    getline(file, str);
                    int pos = line.find(" = ");
                    string ans = line.substr(pos + 3);
                    Bus().length = stof(ans);

                    getline(file, str);
                    int pos = line.find(" = ");
                    string ans = line.substr(pos + 3);
                    Bus().width = stof(ans);
                }
                else if (ans.compare("Truck") == 0)
                {
                    getline(file, str);
                    int pos = line.find(" = ");
                    string ans = line.substr(pos + 3);
                    Truck().length = stof(ans);

                    getline(file, str);
                    int pos = line.find(" = ");
                    string ans = line.substr(pos + 3);
                    Truck().width = stof(ans);
                }
                else if (ans.compare("Bike") == 0)
                {
                    getline(file, str);
                    int pos = line.find(" = ");
                    string ans = line.substr(pos + 3);
                    Bike().length = stof(ans);

                    getline(file, str);
                    int pos = line.find(" = ");
                    string ans = line.substr(pos + 3);
                    Bike().width = stof(ans);
                }
            }            
        }
    }

    while (true)
    {
        
    }

}