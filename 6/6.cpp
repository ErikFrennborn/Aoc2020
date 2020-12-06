#include <cstdio>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <map>
using namespace std;

int parse(vector<vector<string>>*data)
{
    fstream input_file;
    input_file.open("data",ios::in); 
    vector<string> temp;
    if (input_file.is_open())
    {
        string tp;
        while(getline(input_file, tp))
        {
            if (tp.size() == 0){
                data->push_back(temp);
                temp.clear();
            }
            else temp.push_back(tp);
        }
        // Add the reminder
        data->push_back(temp);

    } 
    else cout << "Failed to open file" << endl;       
        input_file.close(); //close the file object.
    return 1;
}

unsigned int task(vector<vector<string>>* data, char (*counter)(map<char, int>, int) )
{
    unsigned int result = 0;
    // #pragma omp parallel for reduction(+:result)
    for (unsigned int group = 0; group < data->size(); group++)
    {
        map<char, int> questions;
        for(unsigned int member_a = 0; member_a < data->at(group).size(); member_a++)
        {
            for (unsigned int index = 0; index < data->at(group).at(member_a).size(); index++)
            {
                char character = data->at(group).at(member_a).at(index);
                if (questions.count(character)) questions[character]++;
                else questions[character] = 1;
            }
        }
        result += (*counter)(questions, data->at(group).size());

    }
    return result;
}

char task_1(map<char,int> a, int group_size)
{
    return a.size();
}

char task_2(map<char,int> a, int group_size)
{
    char all_same = 0;
    for (map<char,int>::iterator it = a.begin(); it != a.end(); it ++)
    {
        if (it->second == group_size) all_same++;
    }
    return all_same;
}

int main()
{
    vector<vector<string>> data;
    parse(&data);
    cout << task(&data, &task_1) << endl;
    cout << task(&data, &task_2) << endl;
    return 1;
}
