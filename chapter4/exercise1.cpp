#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
    Stack stack;
    string str;
    while(cin >> str && !stack.full())//ctrl + d 结束
        stack.push(str);
    if(stack.empty())
    {
        cout << "the stack is empty! no string is read!" << endl;
        return 0;
    }
    stack.peek(str);
    if(stack.size() == 1 && str.empty())
    {
        cout << "the stack is empty! no string is read!" << endl;
        return 0;
    }
    cout << "we got " << stack.size() << "string!" << endl;
    cout << "reverse the order." << endl;
    while(!stack.empty())
    {
        if(stack.pop(str))
            cout << str << " ";
    }
    cout << endl;
    cout << "there is " << stack.size() << " strings in the stack!" << endl;
    return 0;
}