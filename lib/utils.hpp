#ifndef UTILS
#define UTILS

#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
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

// Datastructures
class DDMAP
{
    map<string,vector<tuple<string,int>>> content; // bag -> contain (name, amount)
    map<string,vector<string>> in; // bag -> need in bag
    public:
    void insert(string bag,int amount, string content_bag)
    {
        this->in[content_bag].push_back(bag);
        this->content[bag].push_back(tuple<string,int>(content_bag,amount));
    } 
    int size() {return  this->content.size();}
    vector<tuple<string,int>> get_content(string bag) { return  this->content[bag];}
    vector<string> get_in(string bag) { return  this->in[bag];}
};


// Helper function strings
int split(string* input, vector<string>* output, string delimiter);
int split_to_int(string* input, vector<int>* output, string delimiter);
int replace_string(string* str, string find, string replace);

template <typename A, typename B> 
void mapreduce(B* result,vector<A>* vector, B (*reduce_func)(B, B), B(*map_func) (A) );

int parse(vector<string>*data);



#endif