#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> words;

    if (floating.size() == 0)
    {
        bool allFixed = true;
        for (int i = 0; i < in.size(); i++)
        {
            if (in[i] == '-')
            {
                char alpha = 'a';
                for (int a = 0; a < 26; a++)
                {
                    std::string temp = in;
                    temp[i] = alpha;
                    std::set<std::string> newSet = wordle(temp, floating, dict);
                    words.insert(newSet.begin(), newSet.end());
                    alpha++;
                }
                allFixed = false;
            }
        }
        if (allFixed)
        {
            if (dict.find(in) != dict.end()){
                words.insert(in);
            }
            return words;
        }
    }
    else
    {
        char toFix = floating[0];
        for (int d = 0; d < in.size(); d++)
        {
            std::string temp = in; 
            if (in[d] == '-')
            {
                temp[d] = toFix;
                std::set<std::string> newSet = wordle(temp, floating.substr(1), dict);
                words.insert(newSet.begin(), newSet.end());
            }
        }
        return words;
    }

}

// Define any helper functions here
