#include <iostream>
#include <string>
using namespace std;

class Singleton
{
private:
    int i;
    static Singleton *instance;
    Singleton(int i)
    {
        this->i=i;
    }
    string name;
public:
    static Singleton *getInstance()
    {
        return instance;
    }
    void operator =(const string &s)
    {
        name=s;
    }
    string operator =(const string &s)
    {
        name=s;
    }

    void show()
    {
        cout<<i<<endl;
    }
};
Singleton* Singleton::instance=new Singleton(1);

class A:public Singleton
{

};
class B:public Singleton
{

};

int main()
{
    Singleton *s=Singleton::getInstance();
    Singleton *s2=A::getInstance();
    Singleton *s3=B::getInstance();
    cout<<s<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
    return 0;
}
