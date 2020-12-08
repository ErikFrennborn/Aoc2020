#include "../lib/utils.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <set>
#include <tuple>
#include <vector>

// This args list is a bit longer than I would have wanted but not sure it worth the effert to fix
tuple<int, int> wm( vector<tuple<char, int>>* program, bool can_branch, set<tuple<int, int>>* alt_programs, int _pc, int _acc, set<int>* _seen_pcs)
{
    // Problem variables
    set<int> seen_pcs =*_seen_pcs;
    
    // Setting up vm
    int pc = _pc;
    int acc = _acc;

    // run vm
    while (true)
    {
        // Seen we don't have conditional branches, if we the same pc twice we are stuck in inf loop
        if (seen_pcs.count(pc)) return tuple<int, int>(EXIT_FAILURE,acc);
        if (pc >= program->size()) return tuple<int, int>(EXIT_SUCCESS,acc);
        seen_pcs.insert(pc);
        tuple<char, int> op = program->at(pc);
        switch(get<0>(op))
        {
            case (0):
                if (can_branch)
                {
                    alt_programs->insert(wm(program,false,alt_programs,pc + get<1>(op),acc, &seen_pcs));
                }
                pc++;
                break;
            case (1):
                acc += get<1>(op);
                pc++;
                break;
            case (2):
                if (can_branch)
                {
                    alt_programs->insert(wm(program,false,alt_programs,pc + 1,acc, &seen_pcs));
                }
                pc += get<1>(op);
                break;
            default:
                cout << "Invalid opcode: " << +get<0>(op) << endl;
                exit(EXIT_FAILURE);
        }
    }
    // We can ignore the result of oringal program, for task 2 since we know it will fail
}
int main()
{
    // Set up
    vector<string> data;
    parse(&data);
    set<tuple<int, int>> alt_programs;
    vector<tuple<char, int>> program(data.size());
    set<int> seen_pcs;
    
    // Parse ISA, packing in to a more machine readable state
    transform(data.rbegin(),data.rend(),program.rbegin(), [](string x) {
        size_t space = x.find(" ");
        string op = x.substr(0, space);
        char opcode;
        if (op.compare("nop") == 0 ) opcode = 0;
        else if (op.compare("acc") == 0 ) opcode = 1;
        else if (op.compare("jmp") == 0 ) opcode = 2;
        x.erase(0, space+1);
        int arg = atoi(x.c_str());
        return tuple<char,int>(opcode,arg);
    });
    // Task 1 & 2
    tuple<int, int> result = wm(&program,true,&alt_programs,0,0, &seen_pcs);
    // Task 1
    cout << get<1>(result) << endl;

    // Task 2
    for (set<tuple<int, int>>::iterator state = alt_programs.begin(); state != alt_programs.end(); state++) {
        if (!get<0>(*state))
        {
            cout << get<1>(*state) << endl;
        }
    }
    return 1;
}