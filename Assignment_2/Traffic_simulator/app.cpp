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
#include "Auto.h"

using namespace std;

float roadColor;
int v_l[5]; //lanes taken by ith vehicle  0: car   1:bus   2:truck    3:bike    4: auto

time_t startTime;
time_t timer;

int *count;
float speed;
float min_velocity = 0.1;

int Road::signal;
Tuple Car::acceleration = Tuple(0.01, 0, 0);
Tuple Bike::acceleration = Tuple(0.01, 0, 0);
Tuple Truck::acceleration = Tuple(0.01, 0, 0);
Tuple Bus::acceleration = Tuple(0.01, 0, 0);
Tuple Auto::acceleration = Tuple(0.01, 0, 0);

int Bus::count_per_sec;
int Car::count_per_sec;
int Bike::count_per_sec;
int Truck::count_per_sec;
int Auto::count_per_sec;

int car_l;
int car_w;
int bus_l;
int bus_w;
int truck_l;
int truck_w;
int bike_l;
int bike_w;
int auto_l;
int auto_w;

int bus_count;
int car_count;
int bike_count;
int truck_count;
int auto_count;

void error_callback(int error, const char *description)
{
    cerr << "Error: " << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Road road = Road();

int check_shift(float x_start, float x_end, int lane)
{
    if (lane == -1 || lane == Road::num_lanes)
        return -1;

    if (count[lane] == 1 && road.lanes[lane].at(0) < x_start)
    {
        // cout << x_start << " " << x_end << " loop0 " << road.lanes[lane].at(0) << endl;
        return 1;
    }
    if (count[lane] == 1)
        return -1;

    if (x_start == road.lanes[lane].at(0))
        return -1;
    if (road.lanes[lane].at(road.start_index[lane]) > x_end)
    {
        // cout << x_start << " " << x_end << " loop1 " << road.lanes[lane].at(road.start_index[lane]) << endl;
        return road.start_index[lane];
    }
    else if ((road.lanes[lane].at(road.start_index[lane]) + 0.2 < x_start) && (count[lane] == 2))
    {
        // cout << x_start << " " << x_end << " loop2 " << road.lanes[lane].at(road.start_index[lane]) + 0.2 << endl;
        return road.start_index[lane] + 1;
    }
    else if (count[lane] == 2)
        return -1;

    for (int i = road.start_index[lane]; i < count[lane] - 1; i++)
    {
        if (road.lanes[lane].at(i) + 0.2 < x_start && road.lanes[lane].at(i + 1) > x_end)
        {
            // cout << x_start << " " << x_end << " loop3 " << road.lanes[lane].at(i) + 0.2 << endl;
            return i + 1;
        }
    }

    if (road.lanes[lane].at(count[lane] - 1) + 0.2 < x_start)
    {
        // cout << x_start << " " << x_end << "loop4" << endl;
        return count[lane];
    }
    return -1;
}

void display()
{
    glLoadIdentity();
    road.draw();
    tc();
    light(road.signal);
    time(&timer);

    for (int i = 0; i < road.autos.size(); i++)
    {
        float position_x = road.autos.at(i).position.x;

        int lan = road.autos.at(i).lane;
        int L = road.autos.at(i).n_lanes;
        vector<int> lan_index = road.autos.at(i).lane_index;
        // cout<<lan_index.at(0)<<endl;
        float min = 2.0;

        if (road.autos.at(i).dstToLight <= 0.35)
            road.autos.at(i).velocity.x = 0;
        else if (road.autos.at(i).dstToLight <= 0.5)
            road.autos.at(i).velocity.x = max(road.autos.at(i).velocity.x - Auto::acceleration.x, min_velocity);
        else if (road.autos.at(i).velocity.x < Auto::maxSpeed)
            road.autos.at(i).velocity.x += (Auto::acceleration.x);

        float velocity_x = road.autos.at(i).velocity.x;
        road.autos.at(i).position.x += (-0.005 * velocity_x);

        bool flag = false;
        if (road.autos.at(i).position.x < -1)
            flag = true;

        for (int k = 0; k < L; k++)
        {
            road.lanes[lan + k].at(lan_index.at(k)) = road.autos.at(i).position.x;
            // if (flag) road.start_index[lan + k]++;
        }

        for (int k = 0; k < L; k++)
        {
            float val = road.autos.at(i).position.x - road.lanes[lan + k].at(lan_index.at(k) - 1);
            if (val < min)
                min = val;
        }
        road.autos.at(i).dstToLight = min;

        if (road.autos.at(i).dstToLight < 0.5 && !flag)
        {
            int test_1 = check_shift(road.autos.at(i).position.x - road.autos.at(i).dstToLight, road.autos.at(i).position.x + 0.2, road.autos.at(i).lane - 1);
            int test_2 = check_shift(road.autos.at(i).position.x - road.autos.at(i).dstToLight, road.autos.at(i).position.x + 0.2, road.autos.at(i).lane + L);
            if (test_1 != -1)
            {
                int check_index = road.autos.at(i).lane_index.back();
                for (int p = 0; p < road.cars.size(); p++)
                {
                    for (int k = 0; k < road.cars.at(p).n_lanes; k++)
                    {
                        if (road.cars.at(p).lane + k == lan + L - 1)
                        {
                            if (road.cars.at(p).lane_index.at(k) > check_index)
                                road.cars.at(p).lane_index.at(k)--;
                        }
                        else if (road.cars.at(p).lane + k == lan - 1)
                        {
                            if (road.cars.at(p).lane_index.at(k) >= test_1)
                                road.cars.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.buses.size(); p++)
                {
                    for (int k = 0; k < road.buses.at(p).n_lanes; k++)
                    {
                        if (road.buses.at(p).lane + k == lan + L - 1)
                        {
                            if (road.buses.at(p).lane_index.at(k) > check_index)
                                road.buses.at(p).lane_index.at(k)--;
                        }
                        else if (road.buses.at(p).lane + k == lan - 1)
                        {
                            if (road.buses.at(p).lane_index.at(k) >= test_1)
                                road.buses.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.trucks.size(); p++)
                {
                    for (int k = 0; k < road.trucks.at(p).n_lanes; k++)
                    {
                        if (road.trucks.at(p).lane + k == lan + L - 1)
                        {
                            if (road.trucks.at(p).lane_index.at(k) > check_index)
                                road.trucks.at(p).lane_index.at(k)--;
                        }
                        else if (road.trucks.at(p).lane + k == lan - 1)
                        {
                            if (road.trucks.at(p).lane_index.at(k) >= test_1)
                                road.trucks.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.bikes.size(); p++)
                {
                    for (int k = 0; k < road.bikes.at(p).n_lanes; k++)
                    {
                        if (road.bikes.at(p).lane + k == lan + L - 1)
                        {
                            if (road.bikes.at(p).lane_index.at(k) > check_index)
                                road.bikes.at(p).lane_index.at(k)--;
                        }
                        else if (road.bikes.at(p).lane + k == lan - 1)
                        {
                            if (road.bikes.at(p).lane_index.at(k) >= test_1)
                                road.bikes.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.autos.size(); p++)
                {
                    for (int k = 0; k < road.autos.at(p).n_lanes; k++)
                    {
                        if (road.autos.at(p).lane + k == lan + L - 1)
                        {
                            if (road.autos.at(p).lane_index.at(k) > check_index)
                                road.autos.at(p).lane_index.at(k)--;
                        }
                        else if (road.autos.at(p).lane + k == lan - 1)
                        {
                            if (road.autos.at(p).lane_index.at(k) >= test_1)
                                road.autos.at(p).lane_index.at(k)++;
                        }
                    }
                }

                road.autos.at(i).lane--;
                road.autos.at(i).position.y -= lane_width;
                road.lanes[lan - 1].insert(road.lanes[lan - 1].begin() + test_1, road.autos.at(i).position.x);
                road.lanes[lan + L - 1].erase(road.lanes[lan + L - 1].begin() + road.autos.at(i).lane_index.at(L - 1));
                road.autos.at(i).lane_index.insert(road.autos.at(i).lane_index.begin(), test_1);
                road.autos.at(i).lane_index.pop_back();
                // cout << "Updating car position to lan: " << (lan - 1) << endl;
                // cout << "Updated car position" << endl;
                count[lan + L - 1]--;
                count[lan - 1]++;
            }

            else if (test_2 != -1)
            {
                int check_index = road.autos.at(i).lane_index.front();
                for (int p = 0; p < road.cars.size(); p++)
                {
                    for (int k = 0; k < road.cars.at(p).n_lanes; k++)
                    {
                        if (road.cars.at(p).lane + k == lan)
                        {
                            if (road.cars.at(p).lane_index.at(k) > check_index)
                                road.cars.at(p).lane_index.at(k)--;
                        }
                        else if (road.cars.at(p).lane + k == lan + L)
                        {
                            if (road.cars.at(p).lane_index.at(k) >= test_2)
                                road.cars.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.buses.size(); p++)
                {
                    for (int k = 0; k < road.buses.at(p).n_lanes; k++)
                    {
                        if (road.buses.at(p).lane + k == lan)
                        {
                            if (road.buses.at(p).lane_index.at(k) > check_index)
                                road.buses.at(p).lane_index.at(k)--;
                        }
                        else if (road.buses.at(p).lane + k == lan + L)
                        {
                            if (road.buses.at(p).lane_index.at(k) >= test_2)
                                road.buses.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.trucks.size(); p++)
                {
                    for (int k = 0; k < road.trucks.at(p).n_lanes; k++)
                    {
                        if (road.trucks.at(p).lane + k == lan)
                        {
                            if (road.trucks.at(p).lane_index.at(k) > check_index)
                                road.trucks.at(p).lane_index.at(k)--;
                        }
                        else if (road.trucks.at(p).lane + k == lan + L)
                        {
                            if (road.trucks.at(p).lane_index.at(k) >= test_2)
                                road.trucks.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.bikes.size(); p++)
                {
                    for (int k = 0; k < road.bikes.at(p).n_lanes; k++)
                    {
                        if (road.bikes.at(p).lane + k == lan)
                        {
                            if (road.bikes.at(p).lane_index.at(k) > check_index)
                                road.bikes.at(p).lane_index.at(k)--;
                        }
                        else if (road.bikes.at(p).lane + k == lan + L)
                        {
                            if (road.bikes.at(p).lane_index.at(k) >= test_2)
                                road.bikes.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.autos.size(); p++)
                {
                    for (int k = 0; k < road.autos.at(p).n_lanes; k++)
                    {
                        if (road.autos.at(p).lane + k == lan)
                        {
                            if (road.autos.at(p).lane_index.at(k) > check_index)
                                road.autos.at(p).lane_index.at(k)--;
                        }
                        else if (road.autos.at(p).lane + k == lan + L)
                        {
                            if (road.autos.at(p).lane_index.at(k) >= test_2)
                                road.autos.at(p).lane_index.at(k)++;
                        }
                    }
                }

                road.autos.at(i).lane++;
                road.autos.at(i).position.y += lane_width;
                road.lanes[lan + L].insert(road.lanes[lan + L].begin() + test_2, road.autos.at(i).position.x);
                road.lanes[lan].erase(road.lanes[lan].begin() + road.autos.at(i).lane_index.at(0));
                road.autos.at(i).lane_index.insert(road.autos.at(i).lane_index.begin() + L, test_2);
                road.autos.at(i).lane_index.erase(road.autos.at(i).lane_index.begin());
                // cout << "Updating car position to lan: " << (lan - 1) << endl;
                // cout << "Updated car position" << endl;
                count[lan]--;
                count[lan + L]++;
            }
        }

        road.autos.at(i).draw();
    }
    for (int i = 0; i < road.bikes.size(); i++)
    {
        float position_x = road.bikes.at(i).position.x;

        int lan = road.bikes.at(i).lane;
        int L = road.bikes.at(i).n_lanes;
        vector<int> lan_index = road.bikes.at(i).lane_index;
        // cout<<lan_index.at(0)<<endl;
        float min = 2.0;

        if (road.bikes.at(i).dstToLight <= 0.35)
            road.bikes.at(i).velocity.x = 0;
        else if (road.bikes.at(i).dstToLight <= 0.5)
            road.bikes.at(i).velocity.x = max(road.bikes.at(i).velocity.x - Bike::acceleration.x, min_velocity);
        else if (road.bikes.at(i).velocity.x < Bike::maxSpeed)
            road.bikes.at(i).velocity.x += (Bike::acceleration.x);

        float velocity_x = road.bikes.at(i).velocity.x;
        road.bikes.at(i).position.x += (-0.005 * velocity_x);

        bool flag = false;
        if (road.bikes.at(i).position.x < -1)
            flag = true;

        for (int k = 0; k < L; k++)
        {
            road.lanes[lan + k].at(lan_index.at(k)) = road.bikes.at(i).position.x;
            // if (flag) road.start_index[lan + k]++;
        }

        for (int k = 0; k < L; k++)
        {
            float val = road.bikes.at(i).position.x - road.lanes[lan + k].at(lan_index.at(k) - 1);
            if (val < min)
                min = val;
        }
        road.bikes.at(i).dstToLight = min;

        if (road.bikes.at(i).dstToLight < 0.5 && !flag)
        {
            int test_1 = check_shift(road.bikes.at(i).position.x - road.bikes.at(i).dstToLight, road.bikes.at(i).position.x + 0.2, road.bikes.at(i).lane - 1);
            int test_2 = check_shift(road.bikes.at(i).position.x - road.bikes.at(i).dstToLight, road.bikes.at(i).position.x + 0.2, road.bikes.at(i).lane + L);
            if (test_1 != -1)
            {
                int check_index = road.bikes.at(i).lane_index.back();
                for (int p = 0; p < road.cars.size(); p++)
                {
                    for (int k = 0; k < road.cars.at(p).n_lanes; k++)
                    {
                        if (road.cars.at(p).lane + k == lan + L - 1)
                        {
                            if (road.cars.at(p).lane_index.at(k) > check_index)
                                road.cars.at(p).lane_index.at(k)--;
                        }
                        else if (road.cars.at(p).lane + k == lan - 1)
                        {
                            if (road.cars.at(p).lane_index.at(k) >= test_1)
                                road.cars.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.buses.size(); p++)
                {
                    for (int k = 0; k < road.buses.at(p).n_lanes; k++)
                    {
                        if (road.buses.at(p).lane + k == lan + L - 1)
                        {
                            if (road.buses.at(p).lane_index.at(k) > check_index)
                                road.buses.at(p).lane_index.at(k)--;
                        }
                        else if (road.buses.at(p).lane + k == lan - 1)
                        {
                            if (road.buses.at(p).lane_index.at(k) >= test_1)
                                road.buses.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.trucks.size(); p++)
                {
                    for (int k = 0; k < road.trucks.at(p).n_lanes; k++)
                    {
                        if (road.trucks.at(p).lane + k == lan + L - 1)
                        {
                            if (road.trucks.at(p).lane_index.at(k) > check_index)
                                road.trucks.at(p).lane_index.at(k)--;
                        }
                        else if (road.trucks.at(p).lane + k == lan - 1)
                        {
                            if (road.trucks.at(p).lane_index.at(k) >= test_1)
                                road.trucks.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.bikes.size(); p++)
                {
                    for (int k = 0; k < road.bikes.at(p).n_lanes; k++)
                    {
                        if (road.bikes.at(p).lane + k == lan + L - 1)
                        {
                            if (road.bikes.at(p).lane_index.at(k) > check_index)
                                road.bikes.at(p).lane_index.at(k)--;
                        }
                        else if (road.bikes.at(p).lane + k == lan - 1)
                        {
                            if (road.bikes.at(p).lane_index.at(k) >= test_1)
                                road.bikes.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.autos.size(); p++)
                {
                    for (int k = 0; k < road.autos.at(p).n_lanes; k++)
                    {
                        if (road.autos.at(p).lane + k == lan + L - 1)
                        {
                            if (road.autos.at(p).lane_index.at(k) > check_index)
                                road.autos.at(p).lane_index.at(k)--;
                        }
                        else if (road.autos.at(p).lane + k == lan - 1)
                        {
                            if (road.autos.at(p).lane_index.at(k) >= test_1)
                                road.autos.at(p).lane_index.at(k)++;
                        }
                    }
                }

                road.bikes.at(i).lane--;
                road.bikes.at(i).position.y -= lane_width;
                road.lanes[lan - 1].insert(road.lanes[lan - 1].begin() + test_1, road.bikes.at(i).position.x);
                road.lanes[lan + L - 1].erase(road.lanes[lan + L - 1].begin() + road.bikes.at(i).lane_index.at(L - 1));
                road.bikes.at(i).lane_index.insert(road.bikes.at(i).lane_index.begin(), test_1);
                road.bikes.at(i).lane_index.pop_back();
                // cout << "Updating car position to lan: " << (lan - 1) << endl;
                // cout << "Updated car position" << endl;
                count[lan + L - 1]--;
                count[lan - 1]++;
            }

            else if (test_2 != -1)
            {
                int check_index = road.bikes.at(i).lane_index.front();
                for (int p = 0; p < road.cars.size(); p++)
                {
                    for (int k = 0; k < road.cars.at(p).n_lanes; k++)
                    {
                        if (road.cars.at(p).lane + k == lan)
                        {
                            if (road.cars.at(p).lane_index.at(k) > check_index)
                                road.cars.at(p).lane_index.at(k)--;
                        }
                        else if (road.cars.at(p).lane + k == lan + L)
                        {
                            if (road.cars.at(p).lane_index.at(k) >= test_2)
                                road.cars.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.buses.size(); p++)
                {
                    for (int k = 0; k < road.buses.at(p).n_lanes; k++)
                    {
                        if (road.buses.at(p).lane + k == lan)
                        {
                            if (road.buses.at(p).lane_index.at(k) > check_index)
                                road.buses.at(p).lane_index.at(k)--;
                        }
                        else if (road.buses.at(p).lane + k == lan + L)
                        {
                            if (road.buses.at(p).lane_index.at(k) >= test_2)
                                road.buses.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.trucks.size(); p++)
                {
                    for (int k = 0; k < road.trucks.at(p).n_lanes; k++)
                    {
                        if (road.trucks.at(p).lane + k == lan)
                        {
                            if (road.trucks.at(p).lane_index.at(k) > check_index)
                                road.trucks.at(p).lane_index.at(k)--;
                        }
                        else if (road.trucks.at(p).lane + k == lan + L)
                        {
                            if (road.trucks.at(p).lane_index.at(k) >= test_2)
                                road.trucks.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.bikes.size(); p++)
                {
                    for (int k = 0; k < road.bikes.at(p).n_lanes; k++)
                    {
                        if (road.bikes.at(p).lane + k == lan)
                        {
                            if (road.bikes.at(p).lane_index.at(k) > check_index)
                                road.bikes.at(p).lane_index.at(k)--;
                        }
                        else if (road.bikes.at(p).lane + k == lan + L)
                        {
                            if (road.bikes.at(p).lane_index.at(k) >= test_2)
                                road.bikes.at(p).lane_index.at(k)++;
                        }
                    }
                }

                for (int p = 0; p < road.autos.size(); p++)
                {
                    for (int k = 0; k < road.autos.at(p).n_lanes; k++)
                    {
                        if (road.autos.at(p).lane + k == lan)
                        {
                            if (road.autos.at(p).lane_index.at(k) > check_index)
                                road.autos.at(p).lane_index.at(k)--;
                        }
                        else if (road.autos.at(p).lane + k == lan + L)
                        {
                            if (road.autos.at(p).lane_index.at(k) >= test_2)
                                road.autos.at(p).lane_index.at(k)++;
                        }
                    }
                }

                road.bikes.at(i).lane++;
                road.bikes.at(i).position.y += lane_width;
                road.lanes[lan + L].insert(road.lanes[lan + L].begin() + test_2, road.bikes.at(i).position.x);
                road.lanes[lan].erase(road.lanes[lan].begin() + road.bikes.at(i).lane_index.at(0));
                road.bikes.at(i).lane_index.insert(road.bikes.at(i).lane_index.begin() + L, test_2);
                road.bikes.at(i).lane_index.erase(road.bikes.at(i).lane_index.begin());
                // cout << "Updating car position to lan: " << (lan - 1) << endl;
                // cout << "Updated car position" << endl;
                count[lan]--;
                count[lan + L]++;
            }
        }

        road.bikes.at(i).draw();
    }

    for (int i = 0; i < road.cars.size(); i++)
    {
        float position_x = road.cars.at(i).position.x;
        int lan = road.cars.at(i).lane;
        int L = road.cars.at(i).n_lanes;
        vector<int> lan_index = road.cars.at(i).lane_index;
        // cout<<lan_index.at(0)<<endl;
        float min = 2.0;
        for (int k = 0; k < L; k++)
        {
            float val = road.cars.at(i).position.x - road.lanes[lan + k].at(lan_index.at(k) - 1);
            if (val < min)
                min = val;
        }
        road.cars.at(i).dstToLight = min;
        if (road.cars.at(i).dstToLight <= 0.35)
            road.cars.at(i).velocity.x = 0;
        else if (road.cars.at(i).dstToLight <= 0.5)
            road.cars.at(i).velocity.x = max(road.cars.at(i).velocity.x - Car::acceleration.x, min_velocity);
        else if (road.cars.at(i).velocity.x < Car::maxSpeed)
            road.cars.at(i).velocity.x += (Car::acceleration.x);

        float velocity_x = road.cars.at(i).velocity.x;

        road.cars.at(i).position.x += (-0.005 * velocity_x);
        for (int k = 0; k < L; k++)
        {
            road.lanes[lan + k].at(lan_index.at(k)) = road.cars.at(i).position.x;
        }
        road.cars.at(i).draw();
    }
    for (int i = 0; i < road.buses.size(); i++)
    {
        float position_x = road.buses.at(i).position.x;
        int lan = road.buses.at(i).lane;
        int L = road.buses.at(i).n_lanes;
        vector<int> lan_index = road.buses.at(i).lane_index;
        // cout<<lan_index.at(0)<<endl;
        float min = 2.0;
        for (int k = 0; k < L; k++)
        {
            float val = road.buses.at(i).position.x - road.lanes[lan + k].at(lan_index.at(k) - 1);
            if (val < min)
                min = val;
        }
        road.buses.at(i).dstToLight = min;
        if (road.buses.at(i).dstToLight <= 0.35)
            road.buses.at(i).velocity.x = 0;
        else if (road.buses.at(i).dstToLight <= 0.5)
            road.buses.at(i).velocity.x = max(road.buses.at(i).velocity.x - Bus::acceleration.x, min_velocity);
        else if (road.buses.at(i).velocity.x < Bus::maxSpeed)
            road.buses.at(i).velocity.x += (Bus::acceleration.x);

        float velocity_x = road.buses.at(i).velocity.x;

        road.buses.at(i).position.x += (-0.005 * velocity_x);
        for (int k = 0; k < L; k++)
        {
            road.lanes[lan + k].at(lan_index.at(k)) = road.buses.at(i).position.x;
        }
        road.buses.at(i).draw();
    }
    for (int i = 0; i < road.trucks.size(); i++)
    {
        float position_x = road.trucks.at(i).position.x;
        int lan = road.trucks.at(i).lane;
        int L = road.trucks.at(i).n_lanes;
        vector<int> lan_index = road.trucks.at(i).lane_index;
        // cout<<lan_index.at(0)<<endl;
        float min = 2.0;
        for (int k = 0; k < L; k++)
        {
            float val = road.trucks.at(i).position.x - road.lanes[lan + k].at(lan_index.at(k) - 1);
            if (val < min)
                min = val;
        }
        road.trucks.at(i).dstToLight = min;
        if (road.trucks.at(i).dstToLight <= 0.35)
            road.trucks.at(i).velocity.x = 0;
        else if (road.trucks.at(i).dstToLight <= 0.5)
            road.trucks.at(i).velocity.x = max(road.trucks.at(i).velocity.x - Truck::acceleration.x, min_velocity);
        else if (road.trucks.at(i).velocity.x < Truck::maxSpeed)
            road.trucks.at(i).velocity.x += (Truck::acceleration.x);

        float velocity_x = road.trucks.at(i).velocity.x;

        road.trucks.at(i).position.x += (-0.005 * velocity_x);
        for (int k = 0; k < L; k++)
        {
            road.lanes[lan + k].at(lan_index.at(k)) = road.trucks.at(i).position.x;
        }
        road.trucks.at(i).draw();
    }

    if (difftime(timer, startTime) > 1)
    {
        time(&startTime);
        Road::signal--;
        bike_count = car_count = bus_count = truck_count = auto_count = 0;
        if (Road::signal <= 0)
        {
            for (int i = 0; i < Road::num_lanes; i++)
                road.lanes[i].at(0) = -1000.0;
        }
        // cout << Road::signal << endl;
        for (int i = 0; i < Road::num_lanes; i++)
        {
            int toss = rand() % 10;
            if (toss > 4)
                continue;

            int L = v_l[toss];
            
            float temp = -Road::width + (lane_width * L) / 2.0 + lane_width * i;
            Tuple pos = Tuple(1, temp, 0);
            if (Road::num_lanes - i < L)
                continue;
            for (int k = 0; k < L; k++)
            {
                if (road.lanes[i + k].back() > 0.5)
                    goto exit_loop;
            }
            if (toss == 0)
            {
                if (Road::signal > 0 && car_count >= Car::count_per_sec) continue;
                car_count++;

                Car car = Car(pos);
                car.lane = i;
                car.n_lanes = L;
                for (int k = 0; k < L; k++)
                {
                    road.lanes[i + k].push_back(car.position.x);
                    car.lane_index.push_back(count[i + k]);
                    count[i + k] = count[i + k] + 1;
                }
                road.cars.push_back(car);
            }
            else if (toss == 1)
            {
                if (Road::signal > 0 && bus_count >= Bus::count_per_sec) continue;
                bus_count++;
                
                Bus bus = Bus(pos);
                bus.lane = i;
                bus.n_lanes = L;
                for (int k = 0; k < L; k++)
                {
                    road.lanes[i + k].push_back(bus.position.x);
                    bus.lane_index.push_back(count[i + k]);
                    count[i + k]++;
                }
                road.buses.push_back(bus);
            }
            else if (toss == 2)
            {
                if (Road::signal > 0 && truck_count >= Truck::count_per_sec) continue;
                truck_count++;
                
                Truck truck = Truck(pos);
                truck.lane = i;
                truck.n_lanes = L;
                for (int k = 0; k < L; k++)
                {
                    road.lanes[i + k].push_back(truck.position.x);
                    truck.lane_index.push_back(count[i + k]);
                    count[i + k]++;
                }
                road.trucks.push_back(truck);
            }
            else if (toss == 3)
            {
                if (Road::signal > 0 && bike_count >= Bike::count_per_sec) continue;
                bike_count++;
                
                Bike bike = Bike(pos);
                bike.lane = i;
                bike.n_lanes = L;
                for (int k = 0; k < L; k++)
                {
                    road.lanes[i + k].push_back(bike.position.x);
                    bike.lane_index.push_back(count[i + k]);
                    count[i + k]++;
                }
                road.bikes.push_back(bike);
            }
            else if (toss == 4)
            {
                if (Road::signal > 0 && auto_count >= Auto::count_per_sec) continue;
                auto_count++;
                
                Auto auto1 = Auto(pos);
                auto1.lane = i;
                auto1.n_lanes = L;
                for (int k = 0; k < L; k++)
                {
                    road.lanes[i + k].push_back(auto1.position.x);
                    auto1.lane_index.push_back(count[i + k]);
                    count[i + k]++;
                }
                road.autos.push_back(auto1);
            }
        exit_loop:
            continue;
        }

        for (int i = 0; i < 2 * Road::rows; i++)
            for (int j = 0; j < 40; j++)
                Road::console[i][j] = ' ';

        for (int i = 0; i < road.cars.size(); i++)
        {
            for (int j = road.cars.at(i).lane; j < road.cars.at(i).lane + road.cars.at(i).n_lanes; j++)
                for (int k = 0; k < car_l; k++)
                    if (k + 20 + (int)(road.cars.at(i).position.x / 0.05) < 40 && k + 20 + (int)(road.cars.at(i).position.x / 0.05) > -1)
                        Road::console[Road::num_lanes - j - 1][-k + 19 - (int)(road.cars.at(i).position.x / 0.05)] = 'C';
        }
        for (int i = 0; i < road.buses.size(); i++)
        {
            for (int j = road.buses.at(i).lane; j < road.buses.at(i).lane + road.buses.at(i).n_lanes; j++)
                for (int k = 0; k < bus_l; k++)
                    if (k + 20 + (int)(road.buses.at(i).position.x / 0.05) < 40 && k + 20 + (int)(road.buses.at(i).position.x / 0.05) > -1)
                        Road::console[Road::num_lanes - j - 1][-k + 19 - (int)(road.buses.at(i).position.x / 0.05)] = 'B';
        }
        for (int i = 0; i < road.bikes.size(); i++)
        {
            for (int j = road.bikes.at(i).lane; j < road.bikes.at(i).lane + road.bikes.at(i).n_lanes; j++)
                for (int k = 0; k < bike_l; k++)
                    if (k + 20 + (int)(road.bikes.at(i).position.x / 0.05) < 40 && k + 20 + (int)(road.bikes.at(i).position.x / 0.05) > -1)
                        Road::console[Road::num_lanes - j - 1][-k + 19 - (int)(road.bikes.at(i).position.x / 0.05)] = 'b';
        }
        for (int i = 0; i < road.trucks.size(); i++)
        {
            for (int j = road.trucks.at(i).lane; j < road.trucks.at(i).lane + road.trucks.at(i).n_lanes; j++)
                for (int k = 0; k < truck_l; k++)
                    if (k + 20 + (int)(road.trucks.at(i).position.x / 0.05) < 40 && k + 20 + (int)(road.trucks.at(i).position.x / 0.05) > -1)
                        Road::console[Road::num_lanes - j - 1][-k + 19 - (int)(road.trucks.at(i).position.x / 0.05)] = 'T';
        }
        for (int i = 0; i < road.autos.size(); i++)
        {
            for (int j = road.autos.at(i).lane; j < road.autos.at(i).lane + road.autos.at(i).n_lanes; j++)
                for (int k = 0; k < auto_l; k++)
                    if (k + 20 + (int)(road.autos.at(i).position.x / 0.05) < 40 && k + 20 + (int)(road.autos.at(i).position.x / 0.05) > -1)
                        Road::console[Road::num_lanes - j - 1][-k + 19 - (int)(road.autos.at(i).position.x / 0.05)] = 'A';
        }

        cout << "-------------------------------------------------------------" << endl;
        for (int i = 0; i < 2 * Road::rows; i++)
        {
            for (int j = 0; j < 40; j++)
                cout << Road::console[i][j];
            if (Road::signal > 0) cout << '|';
            cout << endl;
        }
        cout << "-------------------------------------------------------------" << endl;
        cout << "Time: " << (15 - Road::signal) << endl;
    }
}

int main()
{
    load_configuration();
    car_l = Car::length / 0.05;
    car_w = Car::width / 0.05;
    bus_l = Bus::length / 0.05;
    bus_w = Bus::width / 0.05;
    truck_l = Truck::length / 0.05;
    truck_w = Truck::width / 0.05;
    bike_l = Bike::length / 0.05;
    bike_w = Bike::width / 0.05;
    auto_l = Auto::length / 0.05;
    auto_w = Auto::width / 0.05;

    srand(time(0));
    speed = Road::maxSpeed;

    road.lanes = new vector<float>[Road::num_lanes];
    road.start_index = new int[Road::num_lanes];
    count = new int[Road::num_lanes];

    v_l[0] = 1 + (int)(Car::width / lane_width);
    v_l[1] = 1 + (int)(Bus::width / lane_width);
    v_l[2] = 1 + (int)(Truck::width / lane_width);
    v_l[3] = 1 + (int)(Bike::width / lane_width);
    v_l[4] = 1 + (int)(Auto::width / lane_width);

    for (int i = 0; i < Road::num_lanes; i++)
    {
        road.lanes[i].push_back(TLPOSITION);
        count[i] = 1;
        road.start_index[i] = 1;
    }

    time(&startTime);
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    if (!glfwInit())
    {
        // Initialization failed
        cerr << "Initialization failed" << endl;
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Traffic Simulation", NULL, NULL);
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
        ratio = width / (float)height;
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