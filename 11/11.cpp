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
// #include "../lib/utils.hpp"

using namespace std;


int parse(vector<string>*data)
{
    fstream input_file;
    input_file.open("data",ios::in); 
    if (input_file.is_open())
    {
        string tp;
        while(getline(input_file, tp))
        {
            data->push_back(tp);
        }
    } 
    else cout << "Failed to open file" << endl;       
    input_file.close(); //close the file object.
    return 1;
}

char task_adj_1(vector<vector<char>>* input, int i, int j)
{
     char adj = 0;
    for (char k = -1; k < 2; k++)
    {
        for (char l = -1; l < 2; l++)
        {
            if ((k == 0) && (l == 0))continue;
            if ((i+k >= 0) && (i+k < input->size())&&((j+l >= 0) &&(j+l < input->at(0).size())))
            {
                adj += (input->at(i+k).at(j+l) == 2) ? 1 : 0;
            }
        }
    }
    return adj;
}


char task_adj_2(vector<vector<char>>* input, int i, int j)
{
     char adj = 0;
    for (char k = -1; k < 2; k++)
    {
        for (char l = -1; l < 2; l++)
        {
            if ((k == 0) && (l == 0))continue;
            char scaler = 1;
            while (true)
            { 
                char pos_x = i + k* scaler;
                char pos_y = j + l* scaler++;
                if ((pos_x >= 0) && (pos_x < input->size())&&((pos_y >= 0) &&(pos_y < input->at(0).size())))
                {
                    if (input->at(pos_x).at(pos_y) == 0) continue;
                    adj += (input->at(pos_x).at(pos_y) == 2) ? 1 : 0;
                    break;
                }
                else break;
            }
        }
    }
    return adj;
}

int sim(vector<vector<char>>* input, vector<vector<char>>* output, int tolerane )
{
    bool stable = true;
    int occupied = 0;

    for (int i = 0; i < input->size(); i++)
    {
        for (int j = 0; j < input->at(0).size();j++)
        {
           
            if (input->at(i).at(j) == 0) continue;
            char adj = task_adj_2(input, i, j);
            if (input->at(i).at(j) == 1)
            {
                if (adj == 0)
                {
                    occupied++;
                    output->at(i).at(j) = 2;
                    stable = false;
                }
                else output ->at(i).at(j) = 1;
            }
            else if (input->at(i).at(j) == 2)
            {
                occupied ++;
                if(adj >= tolerane)
                {
                    occupied--;
                    output->at(i).at(j) = 1;
                    stable = false;
                } 
                else output->at(i).at(j) = 2;

            }
        }
    }
    for (int i = 0; i< output->size(); i++)
    {
        for (int j = 0; j < output->at(0).size(); j++)
        {
            cout << + output->at(i).at(j);
        }
        cout <<endl;
    }
    cout << endl;
    if (stable) return occupied;
    return 0;   
}

int task_1(vector<vector<char>>* data)
{
    vector<vector<char>> temp1(*data);
    vector<vector<char>> temp2(data->size(), vector<char>(data->at(0).size()));
    vector<vector<char>>* input_ptr = &temp1;
    vector<vector<char>>* output_ptr = &temp2;
    vector<vector<char>>* temp_ptr;
    int occupied = 0;
    while(true)
    {
        occupied = sim(input_ptr,output_ptr,5);
        if (occupied != 0) return occupied;
        temp_ptr = input_ptr;
        input_ptr = output_ptr;
        output_ptr = temp_ptr;
    }
    return occupied;
}

int main()
{
    vector<string> temp;
    parse(&temp);
    vector<vector<char>> data(temp.size());
    for (int i = 0; i < temp.size();i ++)
    {
        for (int j = 0; j < temp.at(i).length(); j++)
        {
            data.at(i).push_back((temp.at(i).at(j) == 'L' ) ? 1 : 0);
        }
    }
    // temp.~vector();
    cout << task_1(&data) << endl;

}