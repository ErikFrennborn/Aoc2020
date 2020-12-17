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


// Borrowed modulo inverser, could be ask to reimplement
long modInverse(long a, long m) 
{ 
    long m0 = m; 
    long y = 0, x = 1; 
  
    if (m == 1) 
        return 0; 
  
    while (a > 1) { 
        // q is quotient 
        long q = a / m; 
        long t = m; 
  
        // m is remainder now, process same as 
        // Euclid's algo 
        m = a % m, a = t; 
        t = y; 
  
        // Update y and x 
        y = x - q * y; 
        x = t; 
    } 
  
    // Make x positive 
    if (x < 0) 
        x += m0; 
  
    return x; 
} 

long task_2(vector<tuple<int,int>>* bus_ids)
{
    //Generting N_i 
    long n = 1;
    for(int i = 0; i < bus_ids->size();i++)
    {
        n *= get<0>(bus_ids->at(i));
    }
    long sum = 0;
    for(int i = 0; i < bus_ids->size();i++)
    {
        long n_i = n/get<0>(bus_ids->at(i));

        long b_i = get<1>(bus_ids->at(i));
        long x_i = modInverse( n_i, get<0>(bus_ids->at(i)));
        sum += n_i*b_i*x_i;
    }
    if (sum < 0) sum += n;
    
    return sum % n;
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
        if (token.at(0) !='x') bus_ids.push_back(tuple<int,int>(stoi(token),stoi(token)-count));
        data.at(1).erase(0, pos + 1);
        count++;
    }
    if (data.at(1).at(0) !='x') bus_ids.push_back(tuple<int,int>(stoi(data.at(1).data()),stoi(data.at(1).data())-count));
    cout << "Task1: " << task_1(&bus_ids, target_time) << endl;
     cout << "Task2: " << task_2(&bus_ids) << endl;
}