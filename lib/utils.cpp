#include "utils.hpp"

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
    return 1;
}

int split_to_int(string* input, vector<int>* output, string delimiter)
{
    size_t pos = 0;
    std::string token;  
    while ((pos = input->find(delimiter)) != std::string::npos)
    {
        token = input->substr(0, pos);
        output->push_back(stoi(token));
        input->erase(0, pos + delimiter.length());
    }
    output->push_back(stoi(input->data()));
    return 1;
}

int replace_string(string* str, string find, string replace)
{
    size_t pos = 0;
    while ((pos = str->find(find)) != std::string::npos)
    {   
        str->replace(pos,find.length(),replace);
    }
    return 1;
}

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
    return 1;
}



template <typename A, typename B> 
void mapreduce(B* result,vector<A>* vector, B (*reduce_func)(B, B), B(*map_func) (A) )
{
    // #pragma omp declare reduction((*reduce_func) : std::vector<unsigned int> : \
    //                           std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus<unsigned int>())) \
    //                 initializer(omp_priv = decltype(omp_orig)(omp_orig.size()))
    B temp = (*result);
    // #pragma omp parallel for reducation(reduce_func: temp)
    for (int i = 0; i < vector->size(); i++)
    {
        temp = reduce_func(map_func(vector->at(i)), temp);
    }
    (*result) += temp;
}