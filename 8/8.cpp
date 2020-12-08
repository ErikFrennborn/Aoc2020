#include "../lib/utils.hpp"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>

class State
{
    public:
        // Pointers to common data
        vector<tuple<char, int>>* program;
        set<tuple<int, int>>* alt_programs;
        vector<thread*>* threads;
        mutex* lock;
        
        // Pointer to clone data
        set<int>* seen_pcs; 
        
        // Primitives
        bool can_branch; 
        int pc;
        int acc;

        // can_branch, seen_pcs, threads, & lock isn't really a bit of machine state but it's convintet to pack it in here

        State(vector<tuple<char, int>>* program, set<tuple<int, int>>* alt_programs, bool can_branch, vector<thread*>* threads, mutex* lock)
        {
            this->program = program;
            this->alt_programs = alt_programs;
            this->threads = threads;
            this->lock = lock;

            this->seen_pcs = new set<int>(); 

            this->can_branch = can_branch;
            this->pc = 0;
            this->acc = 0;
        }
        ~State()
        {  
            // Clean up
            this->seen_pcs->~set();
        }
        State* branch(int pc, int acc)
        {
            State* state = new State(
                this->program,
                this->alt_programs,
                false,
                this->threads,
                this->lock);
            
            state->seen_pcs = new set<int>(*this->seen_pcs);
            state->pc = pc;
            state->acc = acc;
            return state;
        }
};

// This args list is a bit longer than I would have wanted but not sure it worth the effert to fix
tuple<int, int> wm(State* state)
{
    // run vm
    while (true)
    {
        // Seen we don't have conditional branches, if we the same pc twice we are stuck in inf loop
        if (state->seen_pcs->count(state->pc)){ 
            state->lock->lock();
            state->alt_programs->insert(tuple<int, int>(EXIT_FAILURE,state->acc)); 
            state->lock->unlock();
            return(tuple<int, int>(EXIT_FAILURE,state->acc));
        }

        if (state->pc >= state->program->size()) {
            state->lock->lock();
            state->alt_programs->insert(tuple<int, int>(EXIT_SUCCESS,state->acc));
            state->lock->unlock();
            return(tuple<int, int>(EXIT_SUCCESS,state->acc));
        }
        
        state->seen_pcs->insert(state->pc);
        tuple<char, int> op = state->program->at(state->pc);
        switch(get<0>(op))
        {
            case (0):
                if (state->can_branch)
                {
                    State* branch_state = state->branch(state->pc + get<1>(op),state->acc);
                    state->lock->lock();
                    state->threads->emplace_back(new thread(wm,branch_state));
                    state->lock->unlock();
                }
                state->pc++;
                break;
            case (1):
                state->acc += get<1>(op);
                state->pc++;
                break;
            case (2):
                if (state->can_branch)
                {
                    State* branch_state = state->branch(state->pc + 1,state->acc);
                    state->lock->lock();
                    state->threads->emplace_back(new thread(wm,branch_state));
                    state->lock->unlock();
                }
                state->pc += get<1>(op);
                break;
            default:
                cout << "Invalid opcode: " << +get<0>(op) << endl;
                exit(EXIT_FAILURE);
        }
    }
}
int main()
{
    // Set up
    vector<string> data;
    parse(&data);
    set<tuple<int, int>> alt_programs;
    vector<tuple<char, int>> program(data.size());
    vector<thread*> threads;
    mutex lock;

    // Parse ISA, packing in to a more machine readable state
    transform(data.begin(),data.end(),program.begin(), [](string x) {
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
    State* init_state = new State(&program, &alt_programs,true, &threads, &lock);
    tuple<int,int> result = wm(init_state);
    // Task 1
    cout << get<1>(result) << endl;
    

    for (int i = 0; i < init_state->threads->size(); i++)
    {
        init_state->threads->at(i)->join();
    }
    // Task 2
    for (set<tuple<int, int>>::iterator state = alt_programs.begin(); state != alt_programs.end(); state++) {
        if (!get<0>(*state))
        {
            cout << get<1>(*state) << endl;
        }
    }
    return 1;
}