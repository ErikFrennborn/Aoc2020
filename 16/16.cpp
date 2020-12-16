/*
departure location: 41-525 or 538-968
departure station: 50-380 or 395-960
departure platform: 25-507 or 521-953
departure track: 41-401 or 411-953
departure date: 36-274 or 300-970
departure time: 33-739 or 748-959
arrival location: 42-103 or 110-968
arrival station: 36-417 or 438-967
arrival platform: 26-905 or 929-954
arrival track: 49-153 or 163-954
class: 45-710 or 736-970
duration: 47-804 or 827-960
price: 48-250 or 259-970
route: 43-640 or 666-958
row: 32-474 or 493-969
seat: 31-876 or 889-970
train: 49-754 or 762-972
type: 31-761 or 782-963
wagon: 32-455 or 461-956
zone: 39-612 or 629-972
Pack into ranges


your ticket:
myticket

nearby tickets:
In data file
*/

#include "../lib/utils.hpp"
#include <string>
#include <sys/cdefs.h>
#include <vector>
using namespace std;
static int myticket[] = {53,101,83,151,127,131,103,61,73,71,97,89,113,67,149,163,139,59,79,137};
static int ranges[][2] =  {41,525,538,968,50,380,395,
960,25,507,521,953,41,401,411,953,36,274,300,970,33,
739,748,959,42,103,110,968,36,417,438,967,26,905,929,
954,49,153,163,954,45,153,163,954,45,710,736,970,47,
804,827,960,48,250,259,970,43,640,666,958,32,474,493,
969,31,876,889,970,49,754,762,972,31,761,782,963,32,
455,461,956,39,612,629,972};

inline bool range_check(int a, int b ,int c){
    return ( ((a <= c) && (c <= b)) );
}

int task_1(vector<vector<int>>* data, vector<vector<int>*>* output)
{
    long total_error = 0;
    int linewidth = data->at(0).size();
    bool valid_value = false;
    bool valid_ticket = true;
    // #pragma omp parallel for 
    for (int i = 0; i < data->size(); i++)
    {
        for (int j = 0; j <linewidth; j++ )
        {
            int value = data->at(i).at(j);
            for (int k = 0; k < sizeof(ranges)/sizeof(int)/2; k++)
            {
                valid_value |= range_check(ranges[k][0],ranges[k][1], value);
            }
            if (!valid_value) {
                total_error += value;
                valid_ticket = false;
            }
            valid_value = false;
       }
       if (valid_ticket) output->push_back(&data->at(i));
       valid_ticket = true;
    }
    return total_error;
}

map<int,int> task_2(vector<vector<int>*>* data)
{
    int linewidth = data->at(0)->size();
    bool col_vaild = true;
    map<int,vector<int>> fieldmap;
    // Super cache ineffecnt, but short on time
    // #pragma omp parallel for
    for (int k = 0; k < sizeof(ranges)/sizeof(int)/2 -1; k +=2)
    {
        for (int j = 0; j <linewidth; j++ )
        {
            col_vaild = true;
            for (int i = 0; i < data->size(); i++)
            {
                // cout << k << " " << j << " " << i << endl;
                int value = data->at(i)->at(j);
                bool temp = range_check(ranges[k][0],ranges[k][1], value);
                temp |= range_check(ranges[k+1][0],ranges[k+1][1], value);
                col_vaild &= temp; 
            }
            if (col_vaild)
            {
                fieldmap[k/2].push_back(j);
            }
        }
    }
    map<int, vector<int>>::iterator it;
    vector<tuple<int,vector<int>>> cols_group;
    map<int,int> result;
    for ( it = fieldmap.begin(); it != fieldmap.end(); it++ ){
        cols_group.push_back(tuple<int,vector<int>>(it->first,it->second));
    }

    std::sort (cols_group.begin(), cols_group.end(), [](tuple<int,vector<int>>x,tuple<int,vector<int>>y){return (get<1>(x).size() < get<1>(y).size());});
    
    set<int> used;
    for (int i = 0; i < cols_group.size(); i++)
    {
        for (int j = 0; j < get<1>(cols_group.at(i)).size(); j++)
        {
            if (used.find(get<1>(cols_group.at(i)).at(j)) == used.end()) 
            {
                used.insert(get<1>(cols_group.at(i)).at(j));
                result[get<0>(cols_group.at(i))] = get<1>(cols_group.at(i)).at(j);
            }
        }
    }
    return result;
}

int main()
{
    vector<string> strings;
    vector<vector<int>> data;
    vector<vector<int>*> temp;
    parse(&strings);
    
    for (int i = 0; i < strings.size(); i++)
    {
        data.emplace_back(vector<int>());
        split_to_int(&strings.at(i), &data.at(i), ",");
    }
    cout << "Task1: "<< task_1(&data,&temp) << endl;
    map<int,int> result =  task_2(&temp);
    map<int,int>::iterator it;
    long product = 1;
    for (int i = 0; i < 6; i++){
        product *= myticket[result[i]];
    }
    cout << "Task2: "  << product << endl;
}