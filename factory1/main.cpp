#include <iostream>
using namespace std;
class Base
{
public:
    Base()
    {

    }
    ~Base()
    {

    }
    virtual void show()=0;

};
class Base1 : public Base
{
public:
    Base1()
    {

    }
    ~Base1()
    {

    }
    void show()
    {
        cout<<"Base1"<<endl;
    }

};
class Base2 : public Base
{
public:
    Base2()
    {

    }
    ~Base2()
    {

    }
    void show()
    {
        cout<<"Base2"<<endl;
    }
};

class Factory
{
public:
    Factory()
    {

    }
    ~Factory()
    {

    }
    virtual Base* creatBase()=0;
};
class Base1Factory : public Factory
{
public:
    Base* creatBase()
    {
        return new Base1();
    }
};
class Base2Factory : public Factory
{
public:
    Base* creatBase()
    {
        return new Base2();
    }
};



int main()
{
    Base1Factory ba1;
    Base* ba=ba1.creatBase();
    Base2Factory ba2;
    Base* bac=ba2.creatBase();
    ba->show();
    bac->show();
    cout << "Hello World!" << endl;
    return 0;
}

