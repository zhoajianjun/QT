#include <iostream>
#include <vector>

using namespace std;

class mem
{
public:
    mem(int m,int n):a(m),b(n){}
    mem& operator =(const mem& k)
    {
        a=k.a;
        b=k.b;
        return *this;
    }

public:
    int a;
    int b;
};

class role
{
public:
    role(int m,int n):h(m),k(n){}
    mem save()
    {
        mem m(h,k);
        return m;
    }
    void load(mem m)
    {
        h=m.a;
        k=m.b;
    }
    void Show() { cout<<"vitality : "<< h<<", attack : "<< k<<endl; }
    void Attack() { h -= 10; k -= 10; }

private:
    int h;
    int k;
};
class Caretake
{
public:
    Caretake(){}
    void save(mem m){m_mem.push_back(m);}
    mem load(int stat)
    {
        return m_mem.at(stat);
    }


private:
    vector<mem> m_mem;
};


int main()
{
    role ro(100,100);
    ro.Show();
    ro.Attack();
    ro.Attack();
    Caretake ca;
    ca.save(ro.save());
    ro.Show();
    ro.load(ca.load(0));
    ro.Show();
    cout << "Hello World!" << endl;
    return 0;
}

