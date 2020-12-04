#include <algorithm>
#include <cstddef>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
using namespace std;

// g++ 4.cpp -o 4 -fopenmp
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

int replace_string(string* str, string find, string replace)
{
    size_t pos = 0;
    while ((pos = str->find(find)) != std::string::npos)
    {   
        str->replace(pos,find.length(),replace);
    }
}

int parse (vector<vector<string>>* result)
{
    std::ifstream t("data");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    vector<string> datablocks;
    split(&str, &datablocks, "\n\n");
    result->resize(datablocks.size());
    #pragma omp parallel for
    for (int i = 0; i < datablocks.size(); i++)
    {
        replace_string(&datablocks.at(i), "\n", " ");
        split(&datablocks.at(i),&result->at(i)," ");
    }
    
}

int task_1(vector<vector<string>>* datablocks)
{
    /* Attr order 
    * 7 - hgt
    * 5 - byr
    * 6 - iyr
    * 4 - hcl
    * 3 - eyr
    * 2 - ecl 
    * 1 - pid
    * 0 - Cid
    */
    int vaild_blocks = 0;
    // #pragma omp parallel for reduction(+ : vaild_blocks)
    for (int i = 0; i < datablocks->size(); i++)
    {
        unsigned char attr = 0;
        for (int j = 0; j < datablocks->at(i).size(); j++)
        {
            string block = datablocks->at(i).at(j);
            block = block.substr(0,block.find(":"));
            if (block == "pid") attr |= 0b00000010; 
            if (block == "ecl") attr |= 0b00000100;
            if (block == "eyr") attr |= 0b00001000; 
            if (block == "hcl") attr |= 0b00010000;
            if (block == "byr") attr |= 0b00100000;
            if (block == "iyr") attr |= 0b01000000; 
            if (block == "hgt") attr |= 0b10000000; 
        }
        if (attr >= 254) vaild_blocks ++;
    }
    return vaild_blocks;
}

int task_2(vector<vector<string>>* datablocks)
{
    /* Attr order 
    * 7 - hgt
    * 5 - byr
    * 6 - iyr
    * 4 - hcl
    * 3 - eyr
    * 2 - ecl 
    * 1 - pid
    * 0 - Cid
    */
    int vaild_blocks = 0;
    // #pragma omp parallel for reduction(+ : vaild_blocks)
    for (int i = 0; i < datablocks->size(); i++)
    {
        unsigned char attr = 0;
        for (int j = 0; j < datablocks->at(i).size(); j++)
        {
            string block = datablocks->at(i).at(j);
            string tag = block.substr(0,block.find(":"));
            block.erase(0,block.find(":")+1);
            string data = block;
            if (tag == "pid"){
                if (data.length() == 9)
                {
                    attr |= 0b00000010;
                }
            }

            if (tag == "ecl"){
                string colours[] = {"amb", "blu","brn", "gry", "grn","hzl", "oth"};
                for (int k = 0; k < 7; k++)
                {                   
                    if (colours[k].compare(data) == 0)
                    {
                        attr |= 0b00000100;
                        break;
                    } 
                }
            } 
            if (tag == "eyr"){
                unsigned short year = atoi(data.c_str());
                if ((year <= 2030) && (year >= 2020))
                {
                    attr |= 0b00001000; 
                }
            }
            if (tag == "hcl"){
                if (data.at(0) == '#')
                {
                    data .erase(0,1);
                    if (data.length() == 6)
                    {
                        bool vaild = true;
                        for (int k = 0; k < 6;k++)
                        {
                            if (!(((data.at(k) >= '0') && (data.at(k) <= '9')) || ((data.at(k) >='a') && data.at(k) <= 'f')))
                            {
                                vaild = false;
                                break;
                            }
                        }
                        if (vaild) attr |= 0b00010000;
                    }
                    
                }
                
            }
            if (tag == "byr"){
                unsigned short year = atoi(data.c_str());
                if ((year <= 2002) && (year >= 1920)) 
                {
                    attr |= 0b00100000;
                }
            }
            if (tag == "iyr"){
                unsigned short year = atoi(data.c_str());
                if ((year <= 2020) && (year >= 2010)) 
                {
                    attr |= 0b01000000;
                }
            } 
            if (tag == "hgt"){
                string unit = data.substr(data.length()-2,2);
                unsigned short hgt = atoi((data).c_str());
                if (unit == "cm"){
                    if ((hgt <= 193) && (hgt >= 150))
                    {
                        attr |= 0b10000000; 
                    } 
                } else if (unit == "in") {
                    if ((hgt <= 76) && (hgt >= 59))
                    {
                        attr |= 0b10000000;
                    }
                }
            }
        }
        if (attr >= 254) vaild_blocks ++;
    }
    return vaild_blocks;
}

int main ()
{
    vector<vector<string>> datablocks;
    parse(&datablocks);
    cout << task_2(&datablocks) << endl;
}