#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// g++ 3.cpp -o 3 -fopenmp
void parse(vector<string>* map){
    fstream input_file;
    input_file.open("data.txt",ios::in); 
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

int count(vector<string>*map, int slope_right, int slope_down)
{
    int trees = 0;
    int mapwidth = map->at(0).length();
    int x,y = 0;
    #pragma omp parallel for reduction(+:trees)
    for (int i = 0; i< map->size()/slope_down; i++)
    {
        if (map->at(y).substr(x%mapwidth,1).compare("#") == 0) trees++;
        x+=slope_right;
        y+=slope_down;
    }
    return trees;
}

long task_2(vector<string>* map)
{
    int slopes[] = {1,3,5,7};
    long trees = 1;
    #pragma omp parallel for reduction(+:trees)
    for (int i = 0; i < 4; i ++)
    {
        trees = trees * count(map, slopes[i], 1);
        cout <<  count(map, slopes[i], 1)<< endl;
    }
    trees = trees * count(map, 1, 2);
    cout << count(map, 1, 2)<<endl;
    return trees;
}

int main()
{
    vector<string> map;
    parse(&map);
    // task 1 
    cout << count(&map, 3,1) << endl;
    // task 2
    cout << task_2(&map) << endl;
}