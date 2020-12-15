#include <chrono>
#include <cstdlib>
#include <ostream>
#include <pthread.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <unordered_set>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "../lib/utils.hpp"

using namespace std;

int task_1( vector<string>* data)
{
    short dir = 90;
    int x = 0; // growing east
    int y = 0; // growing north
    
    for (int i = 0; i < data->size(); i++)
    {
        char op = data->at(i).at(0);
        int arg = stoi(data->at(i).substr(1, data->at(i).length()-1));

        switch (op) {
            case('N'):
                y += arg;
                break;
            case('S'):
                y -= arg;
                break;
            case('E'):
                x += arg;
                break;
            case('W'):
                x -= arg;
                break;
            case('L'):
                dir = (dir - arg %360  + 360)%360;
                break;
            case('R'):
                dir = (dir + arg %360  + 360)%360;
                break;
            case('F'):
                switch (dir) {
                    case(0):
                       y += arg;
                       break;
                    case(90):
                        x += arg;
                        break;
                    case(180):
                        y -= arg;
                        break;
                    case(270):
                        x -= arg;
                        break;
                    default:
                        cout << "Ilegal dir: " << dir << endl;
                }
                break;
            default:
                cout << "Ilegal op: " << op << endl;
        }
    }
    return abs(x)+abs(y);
}


int task_2( vector<string>* data)
{
    int x = 0; // growing east
    int y = 0; // growing north
    int waypoint[] = {10,1}; //e-w, n-s
    
    for (int i = 0; i < data->size(); i++)
    {
        char op = data->at(i).at(0);
        int arg = stoi(data->at(i).substr(1, data->at(i).length()-1));

        cout << op <<" " << arg<<  " " << x << " " << y << " " << +dir <<" " <<waypoint[0] << " " << waypoint[1] <<endl;
        switch (op) {
            case('N'):
                waypoint[1] += arg;
                break;
            case('S'):
                waypoint[1] -= arg;
                break;
            case('E'):
                waypoint[0] += arg;
                break;
            case('W'):
                waypoint[0] -= arg;
                break;
            case('L'):
                arg = -arg;
            case('R'):
            {
                char rotate = ((arg+360)%360)/90;
                cout << +rotate << endl;
                for (char j = 0; j<rotate;j++)
                {
                    char temp = waypoint[0];
                    waypoint[0] = waypoint[1];
                    waypoint[1] = -temp;
                }
                break;
            }
            case('F'):
                x += waypoint[0]*arg;
                y += waypoint[1]*arg;
                break;
            default:
                cout << "Ilegal op: " << op << endl;
        }
    }
    return abs(x) + abs(y);
}



int main()
{
    vector<string> data;
    parse(&data);
    // cout << task_1(&data) << endl;
    cout << task_2(&data) << endl;
}