#include <bits/c++config.h>
#include <cstddef>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
// g++ 2.cpp -o 2 -fopenmp
class Data
{
    public:
    int higher;
    int lower;
    char charater;
    string pw;

    Data(string pw, char charater, int higher, int lower)
    {
        this->higher = higher;
        this->lower = lower;
        this->pw = pw;
        this ->charater = charater;
    };
};


void parse(vector<Data>* data){
    fstream input_file;
    input_file.open("data.txt",ios::in); 
    if (input_file.is_open())
    {
        string tp;
        while(getline(input_file, tp))
        { //read data from file object and put it into string.
            size_t pos = 0;

            pos = tp.find(" ");
            string interval = tp.substr(0, pos);
            int brack_pos = interval.find("-");
            char lower = atoi(interval.substr(0,brack_pos).c_str());
            interval.erase(0,brack_pos+1);
            char higher = atoi(interval.c_str());
            tp.erase(0, pos + 1);


            pos = tp.find(" ");
            char charater = tp.substr(0, pos-1).at(0);
            tp.erase(0, pos + 1);
            string pw = tp;
            data->push_back(Data(pw,charater,higher,lower));
        }
    }            
    input_file.close(); //close the file object.
}

int task_1(vector<Data>* data)
{
    int valid = 0;
    #pragma omp parallel for reduction(+:valid)
    for (int i = 0; i < data->size(); i ++)
    {
        int num = count(data->at(i).pw.begin(), data->at(i).pw.end(), data->at(i).charater);
        if (num >= data->at(i).lower && num <= data->at(i).higher) 
        {
            valid ++;
        } 
    }
    return valid;
}

int task_2(vector<Data>* data)
{
    int valid = 0;
    // #pragma omp parallel for reduction(+:valid)
    for (int i = 0; i < data->size(); i++)
    {
        bool a = (data->at(i).pw.at(data->at(i).lower - 1) == data->at(i).charater);
        bool b = (data->at(i).pw.at(data->at(i).higher- 1) == data->at(i).charater);
        if (a^b) valid++;
    }
    return valid;
}


int main()
{
    vector<Data> data;
    parse(&data); 
    cout << data.size()<< endl;
    cout << task_2(&data) << endl;
}
