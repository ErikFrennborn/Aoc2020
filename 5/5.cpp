#include <algorithm>
#include <array>
#include <cstddef>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
using namespace std;

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
}


/* Could have piggybacked on parse to solve task 1 to save time, but this is more general.*/
int find_seats(vector<string>* data, vector<short>* seats )
{
    short highest_seat_id = 0;
    for (int i = 0; i < data->size(); i++)
    {   
        unsigned char row = 0;
        for (char j = 0; j < 7; j++)
        {
            if (data->at(i).at(j) == 'B') row|= 1 << (6 -j); 
        }
        unsigned char col = 0;
        for (int j = 0; j < 3; j++)
        {
            if (data->at(i).at(j+7) == 'R') col|= 1 << (2 -j); 
        }
        short seat_id = row*8 + col;
        seats->at(i) = seat_id;
    }
    return 1;
}

bool sortfnc (short i,short j) { return i<j; }

int find_my_seat(vector<short>* seats)
{
    for (int i = 0; i < seats->size()-1; i++)
    {
        if (((seats->at(i))+2) == (seats->at(i+1))) return seats->at(i) +1; 
    }
}

/* We could get row and col back from seat_id by 
 * col = seat_id % 8
 * row = (seat_id - seat_id % 8) / 8 
 * 
 * could be nice to have.
 */
int main()
{
    // Parse data
    vector<string> data;
    parse(&data);
    vector<short> seats(data.size());
    find_seats(&data, &seats);
    sort (seats.begin(), seats.end(), sortfnc);
    // Task 1
    cout << seats.at(seats.size()-1) << endl;
    // Task 2
    cout << find_my_seat(&seats) << endl;
}