#include <atomic>
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

int task_1(vector<tuple<int,int>>* bus_ids, int target_time)
{
    int min = INT_MAX;
    int min_id = 0;
    for(int i = 0; i < bus_ids->size(); i++)
    {
        int temp =  get<0>(bus_ids->at(i)) - target_time % get<0>(bus_ids->at(i)); 
        if((temp >= 0 )&&(temp < min)){
            min=temp;
            min_id =  get<0>(bus_ids->at(i));
        }
    }
    return min_id * min;
}

// long task_2(vector<tuple<int,int>>* bus_ids)
// {
//     long t = 10000000000000;
//     t -= t%get<0>(bus_ids->at(0));
//     cout << t%get<0>(bus_ids->at(0)) << endl;
//     // #pragma omp parallel for schedule(dynamic, 256)
//     for (;;t += get<0>(bus_ids->at(0)))
//     {
//         bool valid = true;
//         for (int i = 1; i < bus_ids->size(); i++)
//         {
//             if ((t+get<1>(bus_ids->at(i)))%get<0>(bus_ids->at(i)) != 0 ) valid = false;
//         }
//         if (valid) break;
//     }
//     return t;
// }


long task_2()
{
/*
  problem:
  t % 17 = 0
  t % 41 = 7
  t % 523 = 17
  t % 13 = 35
  t % 19 = 36
  t % 23 = 40
  t % 787 = 48
  t % 37 = 54
  
  eq:
  t = 17*n1
  t = 41*n2 +7
  t = 523*n3 + 17
  t = 13*n4 + 35
  t = 19*n5 + 36
  t = 23*n6 + 40
  t = 787*n7 + 48
  t = 37*n8 + 54
 
  

*/

}

int main()
{
    vector<string> data;
    parse(&data);
    int target_time = stoi(data.at(0));
    vector<tuple<int,int>> bus_ids;
    int pos;
    std::string token;  
    int count = 0;
    while ((pos = data.at(1).find(",")) != std::string::npos)
    {
        token = data.at(1).substr(0, pos);
        if (token.at(0) !='x') bus_ids.push_back(tuple<int,int>(stoi(token),count));
        data.at(1).erase(0, pos + 1);
        count++;
    }
    for (int i = 0; i<bus_ids.size();i++)
    {
        cout << get<0>(bus_ids.at(i)) << " " << get<1>(bus_ids.at(i)) << endl;
    }
    if (data.at(1).at(0) !='x') bus_ids.push_back(tuple<int,int>(stoi(data.at(1).data()),count));
//     cout << task_1(&bus_ids, target_time) << endl;
     cout << task_2() << endl;
}