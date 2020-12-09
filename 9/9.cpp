#include "../lib/utils.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

// g++ 9.cpp ../lib/utils.cpp -o 9 -fopenmp


int parse(vector<unsigned long>*data)
{
    fstream input_file;
    input_file.open("data",ios::in); 
    if (input_file.is_open())
    {
        string tp;
        while(getline(input_file, tp))
        {
            data->push_back(strtoul(tp.c_str(),NULL,0));
        }
    } 
    else cout << "Failed to open file" << endl;       
    input_file.close(); //close the file object.
    return 1;
}

unsigned long task_1(vector<unsigned long>* data)
{
    for (int i = 25; i < data->size(); i++)
    {
        bool valid = false;
        for (int j = i-25; j < i; j++)
        {
            for (int k = j+1; k < i; k++)
            {
                if (k == j) continue;
                valid |= (data->at(i) == data->at(j) + data->at(k));
            }
        }
        if (!valid) return data->at(i) ;
    }
    return -1;
}

unsigned long task_2(vector<unsigned long>* data, unsigned long weak)
{
    unsigned long sum = 0;
    for (int i = 0; i < data->size(); i++)
    {
        unsigned long lowest =UINT_MAX;
        unsigned long highest = 0;
        for (int j = i+1; j < data->size(); j++)
        {
            lowest = (data->at(j) < lowest) ? data->at(j): lowest;
            highest = (data->at(j) > highest) ? data->at(j): highest;
            sum += data->at(j);
            if (sum == weak){ // Success
                return lowest + highest;
            }
            else if (sum > weak) { // We have gone too far
                sum = 0;
                lowest = 0;
                highest = 0;
                break;
            }
        }
    }
    return -1;
}


int main()
{
    vector<unsigned long> data;
    parse(&data);
    // Task 1
    unsigned long weak = task_1(&data);
    cout << "Task 1: " << weak << endl; 
    /// Task 2
    cout << task_2(&data, weak) << endl;
    return 1;
}