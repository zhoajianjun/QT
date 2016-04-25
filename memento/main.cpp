#include <iostream>
#include <vector>

using namespace std;

class Memento
{
public:
    Memento(int a,int b,int c):a(a),b(b),c(c)
    {

    }
    ~Memento()
    {

    }

    Memento&operator =(const Memento&t)
    {
        a=t.a;
        b=t.b;
        c=t.c;
        return *this;
    }

public:

    int a;
    int b;
    int c;

};
class GameRole
{
public:
    GameRole():a(100),b(100),c(100){}
    Memento Save()
    {
        Memento memento(a,b,c);
        return memento;
    }
    void Load(Memento memento)
    {
        a=memento.a;
        b=memento.b;
        c=memento.c;
    }
    void show()
    {
        cout<<"a:"<<a<<"b:"<<b<<"c:"<<c<<endl;
    }
    void attack()
    {
        a-=10;
        b-=10;
        c-=10;
    }

private:
    int a;
    int b;
    int c;
};
class Caretake
{
public:
    Caretake(){}
    void Save(Memento memento)
    {
        m_memento.push_back(memento);
    }
    Memento load(int state)
    {
        return m_memento[state];
    }

private:
    vector<Memento> m_memento;
};



int main()
{
    Caretake caretake;
    GameRole role;
    role.show();   //初始值
    caretake.Save(role.Save()); //保存状态
    role.attack();
    role.show();  //进攻后
    role.Load(caretake.load(0)); //载入状态
    role.show();  //恢复到状态0
    return 0;
    cout << "Hello World!" << endl;
    return 0;
}

