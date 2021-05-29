#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <string>

using namespace std;

void initialize_exculsion_set(set<string>& );
void process_file(map<string, int>&, const set<string> &, ifstream &);
void user_qurey(const map<string, int>&);
void display_word_count(const map<string, int>&, ofstream &);

int main(int argc, char *argv[])
{
    ifstream ifile("./column.txt");
    ofstream ofile("./column.map");
    if(!ifile && !ofile)
    {
        cerr << "Unable to open file -- bailing out!" << endl;
        return -1;
    }

    set<string> exclusion_set;
    initialize_exculsion_set(exclusion_set);

    map<string, int> word_map;
    process_file(word_map, exclusion_set, ifile);
    user_qurey(word_map);
    display_word_count(word_map, ofile);
    
    return 0;
}

void initialize_exculsion_set(set<string> &exs)
{
    static string _excluded_words[6] = {"a", "an", "or", "the", "and", "but"};

    exs.insert(_excluded_words, _excluded_words + 6);
}

void process_file(map<string, int> &word_count, const set<string> &exclude_set, ifstream &ifile)
{
    string word;
    while(ifile >> word)
    {
        if(exclude_set.count(word))//判断word是否存在于exclude中
            continue;
        word_count[word]++;
    }
}

void user_qurey(const map<string, int> &word_map)
{
    string search_word;
    cout << "Please enter a word to search: q to quit.";
    cin >> search_word;
    while(search_word.size() && search_word != "q")
    {
        map<string, int>::const_iterator it;
        if((it = word_map.find(search_word)) != word_map.end())
            cout << "Found! " << it->first << " occurs " << it->second << " times," << endl;
        else
            cout << search_word << "was not found in text." << endl;
        cin >> search_word;
    }
}

void display_word_count(const map<string, int> &word_map, ofstream &ofile)
{
    map<string, int>::const_iterator it = word_map.begin();
    map<string, int>::const_iterator it_end = word_map.end();
    while(it != it_end)
    {
        ofile << it->first << " ( " << it->second << " ） " << endl;
        it++;
    }
    ofile << endl;    
}