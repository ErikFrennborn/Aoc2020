#include <pthread.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm> 
using namespace std;

int parse(vector<int>*data)
{
    fstream input_file;
    input_file.open("data",ios::in); 
    if (input_file.is_open())
    {
        string tp;
        while(getline(input_file, tp))
        {
            data->push_back(stoi(tp));
        }
    } 
    else cout << "Failed to open file" << endl;       
    input_file.close(); //close the file object.
    return 1;
}

int task_1(vector<int>* data)
{
    int one_diff = 0;
    int three_diff = 1; // 1 because last step will always be +3
    int current_joel = 0;
    for (int i = 0; i < data->size(); i++)
    {
        int diff = data->at(i) - current_joel;
        current_joel = data->at(i);
        if (diff == 1) one_diff++;
        else if (diff == 3) three_diff++;
    }
    return one_diff * three_diff;
}

unsigned long helper_2(vector<vector<int>>* path_to, map<int,unsigned long>* lazy, int index)
{
    unsigned long paths = 0;
    vector<int> path_to_me = path_to->at(index);
    for (int i = 0; i < path_to_me.size(); i++)
    {
        if (lazy->count(path_to_me.at(i))) 
        {
            paths += (*lazy)[path_to_me.at(i)];
        }
        else
        {
            paths +=  helper_2(path_to, lazy, path_to_me.at(i)); 
        }
    }
    (*lazy)[index] = paths;
    return paths;
}


unsigned long task_2(vector<int>* data)
{
    vector<vector<int>> path_to(data->size());
    for (int i = 1; i < data->size(); i++)
    {
        for (int j = 1; j < 4; j++)
        {
            if (i-j < 0) continue;
            if (data->at(i) - data->at(i-j) < 4) 
            {
                path_to.at(i).push_back(i-j);
            }
        }
    }
    map<int,unsigned long> lazy;
    lazy[0] = 1;
    unsigned long result =  helper_2(&path_to, &lazy, path_to.size()-1);
    return  result;

}

int main ()
{
    vector<int> data;
    parse(&data);
    data.push_back(0);
    sort(data.begin(),data.end());
    cout << task_1(&data) << endl;
    cout << task_2(&data) << endl;
}