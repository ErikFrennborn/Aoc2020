#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
using namespace std;

// g++ 3.cpp -o 3 -fopenmp
void parse(vector<string>* map){
    fstream input_file;
    input_file.open("data",ios::in); 
    if (input_file.is_open())
    {
        string tp;
        while(getline(input_file, tp))
        {
            map->push_back(tp);
        }
    } 
    else cout << "Failed to open file" << endl;       
    input_file.close(); //close the file object.
}

#pragma omp declare reduction(vec_int_plus : std::vector<int> : \
                              std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus<int>())) \
                    initializer(omp_priv = decltype(omp_orig)(omp_orig.size()))


long task_2_opt(vector<string>* map, vector<tuple<int,int>>* slopes)
{
    int mapwidth = map->at(0).length();
    const int threads = omp_get_max_threads();
    vector<int> result(slopes->size());

    #pragma omp parallel for reduction(vec_int_plus : result)
    for (int y = 0; y< map->size(); y++)
    {
        for (int j = 0; j < slopes->size(); j++)
        {
            if (y%(get<0>(slopes->at(j))) == 0)
            {
                int x = y*(get<1>(slopes->at(j)))/(get<0>(slopes->at(j)));
                cout << x << " " << get<1>(slopes->at(j)) <<endl;
                if (map->at(y).at(x%mapwidth)== '#')
                {
                    result.at(j)++;
                }
            }
        }  
    }
    long trees = 1;
    for (int i = 0; i < result.size();i++)
    {  
        cout << result.at(i) << endl;
        trees *= result.at(i);
    }
    
    return trees;
}

int count(vector<string>*map, int slope_right, int slope_down)
{
    int trees = 0;
    int mapwidth = map->at(0).size();
    int x,y = 0;
    // #pragma omp parallel for reduction(+:trees)
    for (int i = 0; i< map->size()/slope_down; i++)
    {
        if (map->at(y).at(x%mapwidth) == '#') trees++;
        x+=slope_right;
        y+=slope_down;
    }
    return trees;
}

long task_2(vector<string>* map)
{
    int slopes[] = {1,3,5,7};
    long trees = 1;
    // #pragma omp parallel for reduction(+:trees)
    for (int i = 0; i < 4; i ++)
    {
        trees *= count(map, slopes[i], 1);
        cout <<  count(map, slopes[i], 1)<< endl;
    }
    trees *= count(map, 1, 2);
    cout << count(map, 1, 2)<<endl;
    return trees;
}

int main()
{
    vector<string> map;
    parse(&map);
    // // task 1 
    // cout << count(&map, 3,1) << endl;
    // // task 2
    // cout << task_2(&map) << endl;
    // task 2 opt
    vector<tuple<int, int>> slopes{ tuple<int, int>(1,1),tuple<int, int>(1,3),tuple<int, int>(1,5),tuple<int, int>(1,7),tuple<int, int>(2,1)};
    cout << task_2_opt(&map, &slopes)<<endl;
}