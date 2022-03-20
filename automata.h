
#ifndef AUTOMATA
# define AUTOMATA

#include <iostream>
#include <fstream>
#include <cstring>

#include <vector>
#include <string>
#include <unordered_map>

class Automata
{
    public:
    Automata(const std::string &);
    std::string run_automata(const std::string & input_line);
    private:
    std::vector<std::string> A;
    std::vector<std::string> B;
    std::vector<std::string> Q;
    struct pair_hash
    {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2> &pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };
    typedef std::unordered_map<std::pair<std::string, std::string>, std::pair<std::string, std::string>, pair_hash> Table;
    Table table;
};


# endif