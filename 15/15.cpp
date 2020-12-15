#include <new>
#include <sys/cdefs.h>
#include <vector>
#include <map> 
#include <iostream>
using namespace std;


int main()
{
    map<int,int> seen_earlier = {{6, 0}, {3, 1}, {15, 2}, {13,3},{1, 4}};
    int last_said = 0;
    map<int,int>::iterator it;
    for (int i = seen_earlier.size(); i < 30000000-1; i++)
    {
        it = seen_earlier.find(last_said);
        if (it != seen_earlier.end())
        { // Seen before
            long temp = last_said;
            last_said = (i - it->second);
            seen_earlier[temp] = i;
        }
        else
        {// New
            seen_earlier[last_said] = i;
            last_said = 0;
        }
    }
    cout << last_said << endl;
    return last_said;
}