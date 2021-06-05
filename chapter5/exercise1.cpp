#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef string elemType;

class Stack
{
public:
    virtual ~Stack() {}
    virtual bool pop(elemType &) = 0;
    virtual bool push(const elemType &) = 0;
    virtual bool peek(int index, elemType &) = 0;

    virtual int top() const = 0;
    virtual int size() const = 0;

    virtual bool empty() const = 0;
    virtual bool full() const = 0;
    virtual void print(ostream & = cout) const = 0;
};

ostream &operator<<(ostream &os, const Stack &rhs)
{
    rhs.print(os);
    return os;
}

class LIFO_Stack : public Stack
{
public:
    LIFO_Stack(int capacity = 0) : _top(0)
    {
        if(capacity)
            this->_stack.reserve(capacity);
    }
    int size() const {return this->_stack.size();}
    int top() const {return this->_top;}
    
    bool pop(elemType &elem);
    bool push(const elemType &elem);
    bool peek(int index, elemType &elem);

    bool empty() const {return !this->_top;}
    bool full() const {return this->size() >= this->_stack.max_size();}
    void print(ostream &os = cout) const;
    
private:
    vector<elemType> _stack;
    int _top;
};

bool LIFO_Stack::pop(elemType &elem)
{
    if(this->empty())
        return false;
    elem = this->_stack.back();
    this->_stack.pop_back();
    this->_top--;
    return true;
}

bool LIFO_Stack::push(const elemType &elem)
{
    if(this->full())
        return false;
    this->_stack.push_back(elem);
    this->_top++;
    return true;
}

bool LIFO_Stack::peek(int index, elemType &elem)
{
    if(this->empty())
        return false;
    elem = this->_stack.back();
    index = this->_top;
    return true;
}

void LIFO_Stack::print(ostream &os) const
{
    vector<elemType>::const_reverse_iterator rit = _stack.rbegin(), rend = _stack.rend();

    os << endl;
    while(rit != rend)
        os << *rit++ << endl;
    os << endl;
}

int main()
{
    LIFO_Stack st;
    string str;
    while(cin >> str && ! st.full())
    {
        st.push(str);
    }
    cout << endl << "栈顶为：" << endl;
    st.peek(st.top(), str);
    cout << str << endl;

    st.print();

    return 0;
}