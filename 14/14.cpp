#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <valarray>
#include "../lib/utils.hpp"
#include <bitset>
#include <math.h>
#include <vector>


#define MASKMAX 0b111111111111111111111111111111111111
using namespace std;
class Sim
{  
    private:
        long helper2(string input)
        {
            long result = 0;
            for (int i = 0; i < input.length(); i++)
            {
                if (input.at(i) == '1') result += pow(2,(36-i));
            }
            return result;
        }
        void helper(vector<char>* xs, char index, string previous_string, long addr, long value)
        {
            string rest;
            bitset<36> temp (addr);
            if (xs->size() > (index+1) )
            {
                rest = this->last_mask.substr(xs->at(index)+1, xs->at(index+1) - xs->at(index)-1);
                for (int i = 0; i < rest.length(); i++)
                {
                    if (rest.at(i) == '0')
                    {
                        if (temp[(35-(i + xs->at(index)+1))]) rest.at(i) = '1';
                    }
                }
                helper(xs, index+1, previous_string + "0" + rest, addr, value);
                helper(xs, index+1, previous_string + "1" + rest, addr, value);
            } 
            else
            {
                rest = this->last_mask.substr(xs->at(index) +1, xs->size() - xs->at(index)-2 );
                for (int i = 0; i < rest.length(); i++)
                {
                    if (rest.at(i) == '0')
                    {
                        if (temp[(35-(i + xs->at(index)+1))]) rest.at(i) = '1';
                    }
                }
                long temp_addr = helper2(previous_string+ "0" + rest);  
                this->memsys_addr[temp_addr] = value;
                temp_addr = helper2(previous_string+ "1" + rest);  
                this->memsys_addr[temp_addr] = value;
            } 

        }

    public:
        map<long,long> memsys_value;
        map<long,long> memsys_addr;
        string last_mask;
        long ormask;
        long andmask;

        Sim()
        {
            this->memsys_value= map<long,long>();
            this->memsys_addr= map<long,long>();
        }
        
        void write_mem_value_mod(long addr, long value)
        {   
            long temp = value|this->ormask;
            temp &= this->andmask;
            this->memsys_value[addr] = temp;
        }

        void write_mem_addr_mod(long addr, long value)
        {   
            vector<char> xs;
            bitset<36> temp (addr);
            // cout << "\n\n\n" << this->last_mask << "\n" << temp << "\n" << endl;
            
            for (int i = 0; i < this->last_mask.length(); i++ )
            {
                if (this->last_mask.at(i)=='X')
                {
                   xs.push_back(i);
                } 
            }

            string start = this->last_mask.substr(0,xs.front());
            for (int i = 0; i < start.length(); i++)
            {
                if (start.at(i) == '0')
                {
                    if (temp[(35-i)]) start.at(i) = '1';
                }
            }
            this->helper(&xs, 0, start,addr,value);

        }

        void update_mask(string mask)
        {
            this->last_mask = mask;
            this->ormask = 0;
            this->andmask = MASKMAX;    
    
            for (int i = 0; i < mask.length(); i++ )
            {
                if (mask.at(i)=='1')
                {
                    this->ormask += pow(2,(mask.length()-1-i));
                } 
                else if  (mask.at(i)=='0')
                {
                    this->andmask -= pow(2,(mask.length()-1-i));
                }
            }
        }
};


int  main()
{
    vector<string> data;
    parse(&data);
    Sim sim = Sim();
    for (int i = 0; i<data.size(); i++)
    {
        if (data.at(i).at(1) == 'a')
        { // Mask
            
            vector<string> temp;
            split(&data.at(i), &temp , " ");
            sim.update_mask(temp.at(2));
        }
        else if (data.at(i).at(1) == 'e')
        { // Mem
            vector<string> temp;
            replace_string(&data.at(i),"[", " ");
            replace_string(&data.at(i),"]", " ");
            split(&data.at(i), &temp , " ");
            sim.write_mem_value_mod(stoi(temp.at(1)),stoi(temp.at(4)));
            sim.write_mem_addr_mod(stoi(temp.at(1)),stoi(temp.at(4)));
        }
    }
    map<long, long>::iterator it = sim.memsys_value.begin();
    long sum = 0;
    while (it != sim.memsys_value.end())
    {
        sum += it->second;
        it++;
    }
    cout << "Task 1: "<< sum << endl;
    sum = 0;
    it = sim.memsys_addr.begin();
    while (it != sim.memsys_addr.end())
    {
        // cout << it->first << " " << it->second << endl;
        sum += it->second;
        it++;
    }
    cout << "Task 2: "<< sum << endl;

}