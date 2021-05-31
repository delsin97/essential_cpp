#include "Stack.h"
#include <algorithm>

bool Stack::push(const string &str)
{
    if(full())
        return false;
    _stack.push_back(str);
    return true;
}

bool Stack::pop(string &str)
{
    if(empty())
        return false;
    str = _stack.back();
    _stack.pop_back();
    return true;
}

bool Stack::peek(string &str)
{
    if(empty())
        return false;
    str = _stack.back();
    return true;
}

bool Stack::find(const string &str) const
{
    // vector<string>::const_iterator it = _stack.begin(), endit = _stack.end();
    // while(it != endit)
    // {
    //     if(*it == str)
    //         return true;
    //     it++;
    // }
    // return false;
    vector<string>::const_iterator end_it = _stack.end();
    return ::find(_stack.begin(), end_it, str) != end_it;
}

int Stack::count(const string &str) const
{
    // vector<string>::const_iterator it = _stack.begin(), endit = _stack.end();
    // int num;
    // while(it != endit)
    // {
    //     if(*it == str)
    //         num++;
    //     it++;
    // }
    // return num;
    return ::count(_stack.begin(), _stack.end(), str);
}