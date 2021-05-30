#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

void initial_map(map<string ,vector<string>> &families, ifstream &FileName);
void print_map(const map<string, vector<string>> &families, ostream &os);
void qurey_map(const map<string, vector<string>> &families, const string &family);

int main()
{
    map<string, vector<string>> families;
    ifstream ifile("./families.txt");

    if(!ifile)
    {
        cerr << "Unable to open file!" << endl;
        return -1;
    }

    initial_map(families, ifile);

    string family_name;
    while(1)
    {
        cout << "Please enter a family to search: q to quit.";
        cin >> family_name;

        if(family_name == "q")
            break;
        qurey_map(families, family_name);
    }
    //qurey_map(families, "franz");
    print_map(families, cout);

    return 0;
}

void initial_map(map<string ,vector<string>> &families, ifstream &FileName)
{
    string textline;
    while(getline(FileName, textline))
    {
        string family_name;
        vector<string> child;
        string::size_type pos = 0, prev_pos = 0, text_size = textline.size();

        while((pos = textline.find_first_of(' ', pos)) != string::npos)
        {
            string::size_type len = pos - prev_pos;
            if(!prev_pos)
                family_name = textline.substr(prev_pos, len);
            else
                child.push_back(textline.substr(prev_pos, len));
            prev_pos = ++pos;//修改prev_pos位置
        }

        //处理最后一个小孩名字
        if(prev_pos < text_size)
            child.push_back(textline.substr(prev_pos, pos - prev_pos));

        if(!families.count(family_name))//判断family_name是否存在families中
            families[family_name] = child;
        else 
            cerr << "已经存在姓氏为" << family_name << "的家庭" << endl;
    }
}

void print_map(const map<string ,vector<string>> &families, ostream &os)
{
    map<string, vector<string>>::const_iterator it = families.begin(), endit = families.end();

    while(it != endit)
    {
        os << "the " << it->first << " family ";
        if(it->second.empty())
            os << " has no child. " << endl;
        else
        {
            os << " has " << it->second.size() << " children: ";
            vector<string>::const_iterator sit = it->second.begin(),
                sendit = it->second.end();
            while(sit != sendit)
            {
                os << *sit << " ";
                sit++;
            }    
            os << endl; 
        }
        it++;
    }
}

void qurey_map(const map<string, vector<string>> &families, const string &family)
{
    map<string, vector<string>>::const_iterator it = families.find(family);

    if(it == families.end())
    {
        cout << "Sorry. We don't have " << family << endl;
    }

    else
    {
        cout << "the " << family << " : ";
        if(it->second.empty())
            cout << " has no child. " << endl;
        else
        {
            cout << " has " << it->second.size() << " children: ";
            vector<string>::const_iterator sit = it->second.begin(),
                sendit = it->second.end();
            while(sit != sendit)
                cout << *sit++ << " ";
            cout << endl; 
        }
    }
}
