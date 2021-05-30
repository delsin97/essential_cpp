#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class even_elem
{
public:
    bool operator()(int element)
    {
        return element % 2 ? false : true;
    }
};

int main()
{
    vector<int> input;
    cout << "please input the numbers, q to quit:" << endl;
    istream_iterator<int> in(cin), eos;
    copy(in, eos, back_inserter(input));//输入字母结束
    vector<int>::iterator division = partition(input.begin(), input.end(), even_elem());

    ofstream evenfile("./even.txt");
    ofstream oddfile("./odd.txt");
    if(!evenfile || !oddfile)
    {
        cerr << "can't open file." << endl;
        return -1;
    }
    ostream_iterator<int> even_iter(evenfile, "\n"), odd_iter(oddfile, " ");

    copy(input.begin(), division, even_iter);
    copy(division, input.end(), odd_iter);

    
    return 0;
}