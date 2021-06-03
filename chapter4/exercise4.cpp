#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <cstdio>

using namespace std;

class UserProfile
{
public:
    enum uLevel {Beginner, Intermediate, Advance, Guru};
    UserProfile(string login, uLevel = Beginner);
    UserProfile();

    bool operator==(const UserProfile &rhs);
    bool operator!=(const UserProfile &rhs);

    //查询信息
    string login() const { return _login;}
    string username() const {return _username;}
    int login_count() const {return _time_logged;}
    int guess_count() const {return _guesses;}
    int guess_correct() const {return _correct_guesses;}
    double guess_average() const;
    string level() const;

    //写入数据
    void reset_login(const string &val) {_login = val;}
    void user_name(const string &val) {_username = val;}

    void reset_level(const string &);
    void reset_level(uLevel newlevel) {_user_level = newlevel;}

    void reset_login_count(int val) {_time_logged = val;}
    void reset_guess_count(int val) {_guesses = val;}
    void reset_guess_correct(int val) {_correct_guesses = val;}

    void bump_login_count(int cnt = 1) {_time_logged += cnt;}
    void bump_guess_count(int cnt = 1) {_guesses += cnt;}
    void bump_guess_correct(int cnt = 1) {_correct_guesses += cnt;}

private:
    string _login;
    string _username;
    int _time_logged;
    int _guesses;
    int _correct_guesses;
    uLevel _user_level;

    static map<string, uLevel> _level_map;
    static void init_level_map();
    static string guest_login();
};

inline double UserProfile::guess_average() const
{
    return _guesses ? float(_correct_guesses) / float(_guesses) * 100 : 0.0;
}

inline UserProfile::UserProfile(string login, uLevel level):
    _login(login), _user_level(level), _time_logged(1), _guesses(0)
    , _correct_guesses(0){}

inline UserProfile::UserProfile():_login("guest"), _user_level(Beginner)
    , _time_logged(1), _guesses(0), _correct_guesses(0)
{
    static int id = 0;
    char buffer[16];

    sprintf(buffer, "%d", id++);//将整数转化为字符串 别用itoa()，linux下面没有这个函数
    _login += buffer;//对于guess，加入一个独特的表识码
}

inline bool UserProfile::operator==(const UserProfile &rhs)
{
    if(_login == rhs.login() && _username == rhs.username())
        return true;
    return false;
}

inline bool UserProfile::operator!=(const UserProfile &rhs)
{
    return !(*this==rhs);
}

inline string UserProfile::level() const
{
    static string _level_table[] = {"Beginner", "Intermediate", "Advance", "Guru"};
    return _level_table[_user_level];
}


ostream &operator<<(ostream &os, const UserProfile &rhs)
{
    // login level login_count guess_count correct_count percentage
    os << rhs.login() << " " <<rhs.level() << " " << rhs.login_count()
       << " " << rhs.guess_count() << " " << rhs.guess_correct() << " "
        << rhs.guess_average() << endl;
    return os;
}

map<string, UserProfile::uLevel> UserProfile::_level_map;

void UserProfile::init_level_map()
{
    _level_map["Beginner"] = Beginner;
    _level_map["Intermediate"] = Intermediate;
    _level_map["Advance"] = Advance;
    _level_map["Guru"] = Guru;
}

inline void UserProfile::reset_level(const string &level)
{
    map<string, uLevel>::iterator it;
    if(_level_map.empty())
        init_level_map();
    
    _user_level = ((it = _level_map.find(level)) != _level_map.end()) ? it->second : Beginner;
}

istream &operator>>(istream &is, UserProfile &rhs)
{
    string login, level;
    is >> login >> level;

    int lcount, gcount, ccount;
    is >> lcount >> gcount >> ccount;

    rhs.reset_login(login);
    rhs.reset_level(level);

    rhs.reset_login_count(lcount);
    rhs.reset_guess_count(gcount);
    rhs.reset_guess_correct(ccount);
    return is;
}

int main()
{
    UserProfile anon;
    cout << anon;

    UserProfile anon_too;
    cout << anon_too;

    UserProfile anna("AnnaL", UserProfile::Guru);
    cout << anna;

    anna.bump_guess_count(20);
    anna.bump_guess_correct(10);
    anna.bump_login_count();

    cout << anna;

    cin >> anon;
    cout << anon;

    return 0;
}