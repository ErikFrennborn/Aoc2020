#include <cstdio>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <map>
using namespace std;

using FunctionPointer = char(*)(map<char,int>, int);

template <FunctionPointer function>
static void wrapper_function(map<char,int> a, int b)
{
    function(a,b);
}

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
#pragma omp declare reduction(vec_int_plus : std::vector<unsigned int> : \
                              std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus<unsigned int>())) \
                    initializer(omp_priv = decltype(omp_orig)(omp_orig.size()))

int task(vector<vector<string>>* data, FunctionPointer functions[], vector<unsigned int>* result)
{
    vector<unsigned int> temp_result(result->size(),0);
    #pragma omp parallel for reduction(vec_int_plus : temp_result)
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
        for (int i = 0; i < result->size(); i++)
        {
            temp_result.at(i) += functions[i](questions, data->at(group).size());
        }
    }
    for (int i = 0; i < result->size(); i++)
    {
        result->at(i) = temp_result.at(i);
    }
    return 1;
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
    FunctionPointer functions[] = {task_1,task_2};
    vector<unsigned int> result(2);
    task(&data, functions, &result);
    cout << result.at(0) << " " << result.at(1) << endl;
    return 1;
}
