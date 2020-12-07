#include "../lib/utils.hpp"
#include <functional>
#include <string>
using namespace std;
// g++ 7.cpp -o 7 -fopenmp

int parse(DDMAP*data, vector<string>* lines)
{
    fstream input_file;
    input_file.open("data",ios::in); 
    if (input_file.is_open())
    {
        string tp;
        while(getline(input_file, tp))
        {
            lines->push_back(tp);
        }
    }
    else cout << "Failed to open file" << endl;       
    input_file.close(); //close the file object.
    vector<vector<string>> temp_lines(lines->size());
    vector<string> temp(*lines);
    for (int i = 0; i < temp.size(); i++)
    {
        temp_lines.at(i) = vector<string>();
        split(&temp.at(i), &temp_lines.at(i), " ");
    }
    // Create hashmap
    map<string,vector<string>> bags;
    for (int i = 0; i < temp_lines.size(); i++)
    {
        string bag = temp_lines.at(i).at(0) + " " + temp_lines.at(i).at(1);
        for (int j = 0; j < (temp_lines.at(i).size()-4)/4; j++)
        {
            data->insert((temp_lines.at(i).at(0) + " " + temp_lines.at(i).at(1)), (atoi(temp_lines.at(i).at(j*4+4).c_str())), (temp_lines.at(i).at(j*4+5) + " " + temp_lines.at(i).at(j*4+6)) );
        }
    }
    return 1;
}

int rerecursively_find(string bag,DDMAP* bags, set<string>* unique_bags)
{
    vector<string> target_bags = bags->get_in(bag);
    for (int i = 0; i < target_bags.size(); i++)
    {
        if (!(unique_bags->find(target_bags.at(i)) != unique_bags->end()))
        {
            unique_bags->insert(target_bags.at(i));
            rerecursively_find(target_bags.at(i),bags,unique_bags);
        }
    }
}


int rerecursively_count(string bag,DDMAP* bags)
{
    vector<tuple<string,int>> target_bags = bags->get_content(bag);
    int count = 0;
    for (int i = 0; i < target_bags.size(); i++)
    {
        if (target_bags.size() != 0)
        {
            count += get<1>(target_bags.at(i)) * rerecursively_count(get<0>(target_bags.at(i)),bags);
        }
    }
    return count +1 ;
}

int main()
{
    // Set up
    vector<string>lines;
    DDMAP data;
    parse(&data, &lines);
    
    // Task 1
    set<string> unique_bags;
    rerecursively_find("shiny gold", &data, &unique_bags);
    cout << "Task 1: " << unique_bags.size() << endl;

    // Task 2
    int count = rerecursively_count("shiny gold", &data);
    // -1 to not count shiny gold bag
    cout << "Task 2 : " << count - 1 << endl;

}