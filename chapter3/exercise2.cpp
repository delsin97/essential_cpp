#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>//调用sort函数

using namespace std;

class LessThan
{
public:
    bool operator()(const string &s1, const string &s2)//function object
    {
        return s1.size() < s2.size();
    }
};

void print(const vector<string> &vec, ofstream &ofile)
{
    vector<string>::const_iterator it = vec.begin(), end_it = vec.end();

    while(it != end_it)
        ofile << *it++ << endl;
    ofile << endl;
}

int main(int argc, char *argv[])
{
    ifstream ifile("./column.txt");
    ofstream ofile("./column.sort");
    
    if(!ifile || !ofile)
    {
        cerr << "Unable to open file!" << endl;
        return -1;
    }

    vector<string> text;
    string word;

    while(ifile >> word)
        text.push_back(word);

    sort(text.begin(), text.end(), LessThan());

    print(text, ofile);
    return 0;
}