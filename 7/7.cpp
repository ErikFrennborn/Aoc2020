#include <cstdlib>
#include <iterator>
#include <string>
#include <fstream>
#include <streambuf>
#include <tuple>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
using namespace std;
// g++ 7.cpp -o 7 -fopenmp

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

int split(string* input, vector<string>* output, string delimiter)
{
    size_t pos = 0;
    std::string token;  
    while ((pos = input->find(delimiter)) != std::string::npos)
    {
        token = input->substr(0, pos);
        output->push_back(token);
        input->erase(0, pos + delimiter.length());
    }
    output->push_back(input->data());
}

int rerecursively_find(string bag,map<string,vector<string>>* bags, set<string>* unique_bags)
{
    vector<string> target_bags = (*bags)[bag];
    for (int i = 0; i < target_bags.size(); i++)
    {
        if (!(unique_bags->find(target_bags.at(i)) != unique_bags->end()))
        {
            unique_bags->insert(target_bags.at(i));
            rerecursively_find(target_bags.at(i),bags,unique_bags);
        }
    }
}

int task_1(vector<string>*data)
{  
    vector<vector<string>> data2(data->size());
    vector<string> temp(*data);
    for (int i = 0; i < temp.size(); i++)
    {
        data2.at(i) = vector<string>();
        split(&temp.at(i), &data2.at(i), " ");
    }
    // Create hashmap
    map<string,vector<string>> bags;
    for (int i = 0; i < data2.size(); i++)
    {
        string bag = data2.at(i).at(0) + " " + data2.at(i).at(1);
        for (int j = 0; j < (data2.at(i).size()-4)/4; j++)
        {
            bags[data2.at(i).at(j*4+5) + " " + data2.at(i).at(j*4+6)].push_back(bag);
        }
    }
    // Find which bag gold can be place, and then find which these bag can be placed in
    set<string> unique_bags;
    for (int i = 0; i < data->size(); i++)
    {
        size_t contains = data->at(i).find("contain");
        size_t found = data->at(i).find("shiny gold", contains);
        if (found != string::npos)
        {
            string bag = data2.at(i).at(0) + " " + data2.at(i).at(1);
            unique_bags.insert(bag);
            rerecursively_find(bag, &bags, &unique_bags);
        }
    }
    return unique_bags.size();
}

int rerecursively_count(string bag,map<string,vector<tuple<string,int>>>* bags)
{
    vector<tuple<string,int>> target_bags = (*bags)[bag];
    int count = 0;
    for (int i = 0; i < target_bags.size(); i++)
    {
        if (target_bags.size() != 0)
        {
            count += get<1>(target_bags.at(i)) * rerecursively_count(get<0>(target_bags.at(i)),bags);
        }
    }
    return count +1 ;
}

int task_2(vector<string>*data)
{  
    vector<vector<string>> data2(data->size());
    vector<string> temp(*data);
    for (int i = 0; i < temp.size(); i++)
    {
        data2.at(i) = vector<string>();
        split(&temp.at(i), &data2.at(i), " ");
    }
    // Create hashmap
    map<string,vector<tuple<string,int>>> bags;
    for (int i = 0; i < data2.size(); i++)
    {
        string bag = data2.at(i).at(0) + " " + data2.at(i).at(1);
        for (int j = 0; j < (data2.at(i).size()-4)/4; j++)
        {
            bags[bag].push_back( tuple<string, int>( (data2.at(i).at(j*4+5) + " " + data2.at(i).at(j*4+6)), (atoi(data2.at(i).at(j*4+4).c_str())) ));
        }
    }
    // Find which bag gold can be place, and then find which these bag can be placed in
    int count = 0;
    for (int i = 0; i < data->size(); i++)
    {
        string bag = data2.at(i).at(0) + " " + data2.at(i).at(1);
        if ("shiny gold" == bag)
        {
            count = rerecursively_count(bag, &bags);
            break;
        }
    }
    // -1 to not count shiny gold bag
    return count - 1;
}

int main()
{
    vector<string>data;
    parse(&data);
    cout << task_1(&data) << endl;
    cout << task_2(&data) << endl;

}