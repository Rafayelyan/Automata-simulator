#include "automata.h"

using std::pair;
using std::vector;
using std::string;
using std::unordered_map;

#include <iostream>
#include <fstream>
#include <cstring>

Automata::Automata(const std::string & file_path)
{
    /*
        do some parsing from file and get result
        A = {   } vector of input alphabet
        B = {   } vector of output alphabet
        Q = {   } vector of states
        
        and table discribing lambda and delta functions
            unordered_map<pair<state, data>, pair<state, data>>
     */

    std::fstream in_file;

    in_file.open(file_path, std::ios::out | std::ios::in);
    if(!in_file)
    {
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    vector<vector<std::string>*> vecs = {&A, &B, &Q}; 
    while (!in_file.eof())
    {
        char temp[255];
        char *str = nullptr;
        int counter = 0;
        while (counter < 3 && in_file.getline(temp, 255))
        {
            str = strtok(temp, ", ");
            while (str != NULL)
            {
                vecs[counter]->push_back(str);
                str = strtok(NULL, ", ");
            }          
            ++counter;
            bzero(temp, 255);
        }
        bzero(temp, 255);
        counter = 0;
        while (in_file.getline(temp, 255))
        {
            int i = 0;
            if (temp[0] == '\0') 
            {
                continue;
            }
            str = strtok(temp, " | ");
            std::string b;
            std::string q;
            std::string tempStr;
            while (str != NULL)
            {
                tempStr = str;
                b = tempStr.substr(0, tempStr.find(','));
                q = tempStr.substr(tempStr.find(',') + 1, tempStr.size() - 1);
                table.insert(std::make_pair(std::make_pair(Q[counter], A[i]), std::make_pair(q, b)));
                str = strtok(NULL, " | ");
                ++i;
            }
            ++counter;
            i = 0;
        }
    }
}

std::string Automata::run_automata(const std::string & input_line)
{
    std::string state = Q[0];
    std::string data;
    string res_line;

    for (int i = 0; i < (int)input_line.size(); ++i)
    {
        std::string temp({input_line[i]});
        auto next_step = table.find(std::make_pair(state, temp));
        #ifdef DEBUG
        std::string prev_step = state;
        #endif
        state = next_step->second.first;
        data = next_step->second.second;
        #ifdef DEBUG
        std::cout<<"("<<input_line[i]<<", "<<prev_step<<") -> ("<<data<<", "<<state<<")"<<std::endl;
        #endif
        res_line.append(data);
    }
    return (res_line);
}